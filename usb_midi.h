#ifndef USB_MIDI_H
#define USB_MIDI_H

#include <stdint.h>

/**
 * The midi channel used to transmit all MIDI packets. Incoming data is not
 * filtered on this channel.
 * Should be a value from 0 to 15.
 */
#define MIDI_CHANNEL	0

/**
 * Only these MIDI commands are supported for now. Other MIDI packets are
 * filtered out.
 */
typedef enum {
	NOTE_OFF		= 0x80,
	NOTE_ON			= 0x90,
	CONTROL_CHANGE	= 0xB0
} MidiCommand;

/**
 * Structure of a regular MIDI packet.
 */
typedef struct {
	MidiCommand command;
	uint8_t	key;
	uint8_t value;
} MidiPacket;

/**
 * Initialize.
*/
void midi_initialize( void );

/**
 * Set the channel to receive incoming packets on. -1 listens to all channels.
 */
void midi_set_listen_channel( int8_t new_channel );

/**
 * Tasks, has to be called regularly. Checks if new MIDI packets were received.
 */
void midi_tasks( void );

/**
 * Transmits an array of MIDI packets. Maximum 16 packets at once.
 * Returns -1 if the transmit handle is still processing a transaction and
 * transmission was aborted. With Full Speed USB, a packet can be sent every 1
 * millisecond.
 */
int8_t midi_send( MidiPacket packet[], uint8_t num );

/**
 * External function that is called when new MIDI packets are received. Maximum
 * amount of received packets is 16.
 */
extern void midi_receive( MidiPacket packet[], uint8_t num );

#endif // USB_MIDI_H
