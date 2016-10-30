# FDRbox: https://github.com/koenaad/FDRbox
# by Koenraad Verheyden @koenaad

from _Framework.ButtonElement import ButtonElement
from _Framework.ControlSurface import ControlSurface
from _Framework.InputControlElement import MIDI_CC_TYPE
from _Framework.MixerComponent import MixerComponent

MIDI_CHANNEL = 0    # has to match with channel programmed in firmware

#   TODO
#   combine multiple devices to control 16/24/32/... tracks
#   implemmentation:
#       check code used for APC's
#       https://github.com/gluon/AbletonLive9_RemoteScripts/blob/master/_APC/APC.py

class FDRbox( ControlSurface ):

    def __init__( self, c_instance ):
        ControlSurface.__init__( self, c_instance )

        with self.component_guard():
            self._suggested_input_port = 'FDRbox'
            self._suggested_output_port = 'FDRbox'

            # ButtonElement( is_momentary, msg_type, channel, identifier )
            faders = [ ButtonElement( False, MIDI_CC_TYPE, MIDI_CHANNEL, i ) for i in range( 8 ) ]

            self._mixer = MixerComponent( 8 )
            for i in range( 8 ):
                self._mixer.channel_strip( i ).set_volume_control( faders[ i ] )

#       self.log_message( 'init' )

    def disconnect( self ):
        ControlSurface.disconnect( self )
        self._mixer = None

#       self.log_message( 'disconnected' )
