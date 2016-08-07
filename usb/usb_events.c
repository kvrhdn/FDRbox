/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/
#include "system.h"

#include "usb_midi.h"

#include "usb_device.h"
#include "usb_device_midi.h"


bool USER_USB_CALLBACK_EVENT_HANDLER( USB_EVENT event, void *pdata, uint16_t size )
{
	switch( event ) {
		case EVENT_TRANSFER:
		case EVENT_SOF:
		case EVENT_SUSPEND:
		case EVENT_RESUME:
			break;

		case EVENT_CONFIGURED:
			// When the device is configured, we can (re)initialize the MIDI code
			midi_initialize();
			break;

		case EVENT_SET_DESCRIPTOR:
		case EVENT_EP0_REQUEST:
		case EVENT_BUS_ERROR:
		case EVENT_TRANSFER_TERMINATED:											// TODO check usefulness
    // A user transfer was terminated by the stack.  This event will pass back
    // the value of the handle that was terminated.  Compare this value against
    // the current valid handles to determine which transfer was terminated.

		default:
			break;
	}
	return true;
}

/*******************************************************************************
 End of File
*/
