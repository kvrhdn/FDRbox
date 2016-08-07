#include "usb_midi.h"

#include "usb.h"
#include "usb_device_midi.h"
#include "fixed_address_memory.h"
#include "led.h"

/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.																*/
/* Buffers are 64 bytes, this allows a max of 16 USB MIDI packets.				*/
static uint8_t recv_data_buffer[ 64 ] @ DEVCE_AUDIO_MIDI_RX_DATA_BUFFER_ADDRESS;
static uint8_t send_data_buffer[ 64 ] @ DEVCE_AUDIO_MIDI_EVENT_DATA_BUFFER_ADDRESS;

static USB_HANDLE usb_send_handle;
static USB_HANDLE usb_recv_handle;

/* The channel we are listening on.												*/
static int8_t listen_channel = -1;

/* Rearm the OUT endpoint for the next packet, this will overwrite the old data	*/
#define REARM_OUT_ENDPOINT()													\
	usb_recv_handle = USBRxOnePacket( USB_DEVICE_AUDIO_MIDI_ENDPOINT, recv_data_buffer, 64 );

void midi_initialize()
{
	usb_send_handle = NULL;
	usb_recv_handle = NULL;

	// enable the HID endpoint
	USBEnableEndpoint( USB_DEVICE_AUDIO_MIDI_ENDPOINT, USB_OUT_ENABLED | USB_IN_ENABLED | USB_HANDSHAKE_ENABLED | USB_DISALLOW_SETUP );

	REARM_OUT_ENDPOINT();
}

void midi_set_listen_channel( int8_t new_channel )
{
	listen_channel = new_channel;
}

void midi_tasks()
{
	if ( USBHandleBusy( usb_recv_handle ) )
		return;

	uint8_t len = USBHandleGetLength( usb_recv_handle );
	uint8_t count = 0;	// the amount of supported packets

	USB_AUDIO_MIDI_EVENT_PACKET * data = (USB_AUDIO_MIDI_EVENT_PACKET *)recv_data_buffer;
	MidiPacket packet_buffer[ 16 ];

	while ( len >= sizeof( USB_AUDIO_MIDI_EVENT_PACKET ) ) {
		// check USB MIDI header for supported types
		switch ( data->CodeIndexNumber ) {
			case MIDI_CIN_NOTE_ON:
			case MIDI_CIN_NOTE_OFF:
			case MIDI_CIN_CONTROL_CHANGE:
				// filter on channel
				if ( listen_channel == -1 || listen_channel == ( data->MIDI_0 & 0x0F ) ) {
					// check for supported MIDI commands
					switch ( data->MIDI_0 & 0xF0 ) {
						case NOTE_ON:
						case NOTE_OFF:
						case CONTROL_CHANGE:
							packet_buffer[ count ].command =	data->MIDI_0 & 0xF0;
							packet_buffer[ count ].key =		data->MIDI_1;
							packet_buffer[ count ].value =		data->MIDI_2;

							++count;
							break;

						default:
							break;
					}
				}
				break;

			default:
				break;
		}
		len -= sizeof( USB_AUDIO_MIDI_EVENT_PACKET );
		data += 1;
	}
	led_blink();
	REARM_OUT_ENDPOINT();

	if ( count )
		midi_receive( packet_buffer, count );
}

int8_t midi_send( MidiPacket packet[], uint8_t num )
{
	if ( USBHandleBusy( usb_send_handle ) )
		return -1;	// transmission still in progress

	if ( num > 16 )
		num = 16;	// limit to 16 packets

	USB_AUDIO_MIDI_EVENT_PACKET * data = (USB_AUDIO_MIDI_EVENT_PACKET *)send_data_buffer;

	for ( uint8_t i = 0; i < num; ++i ) {
		/* v[ 0 ]	CableNumber		:4	= 0											
		 *			CodeIndexNumber :4	= command: see midi10.pdf, table 4-1, these values match for all the commands we support
		 */
		data[ i ].v[ 0 ] = ( packet[ i ].command >> 4 );
		data[ i ].MIDI_0 = packet[ i ].command | MIDI_CHANNEL;
		data[ i ].MIDI_1 = packet[ i ].key;
		data[ i ].MIDI_2 = packet[ i ].value;
	}

	usb_send_handle = USBTxOnePacket( USB_DEVICE_AUDIO_MIDI_ENDPOINT, &send_data_buffer, num * sizeof( USB_AUDIO_MIDI_EVENT_PACKET ) );
	led_blink();
	return 0;
}
