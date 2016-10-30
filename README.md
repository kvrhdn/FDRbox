FDRbox
===
By Koenraad Verheyden - [@koenaad](https://twitter.com/koenaad)

Description
---
A simple USB MIDI controller with 8 faders.

[Album with images](http://imgur.com/a/iQqRE)

Status
---
I assembled a couple of boards and __they all work completely__!

TODO
* finish off design: find fadercaps, some screws and feet.
* clean up code.

Code
---
[```code/```](code/) is a subtree of [PIC16F145x_MIDI](https://github.com/koenaad/PIC16F145x_MIDI). The application specific code is in [```main.c```](code/main.c).

This project uses the USB stack from [Microchip Libraries for Applications](http://microchip.com/mla).  
MLA is licensed under the Apache License version 2.0. (See: [microchip.com/mla_license](http://microchip.com/mla_license))

PCB
---
[```pcb/```](pcb/) contains the schematics and design of the PCB. The entire PCB was designed using [KiCad](http://kicad-pcb.org/), an open-source software suite for EDA.

PDF's of the schematic are placed in [```pcb/output/```](pcb/output/).  
You can find the Gerber files I used here: [```pcb/output/FDRbox_v0.1_gerber/```](pcb/output/FDRbox_v0.1_gerber/)

Frontpanel
---
I also designed a frontpanel, [```frontpanel```](frontpanel/) contains the SVG I used to lasercut it.

Ableton Live MIDI Remote Script
---
[```Ableton Live MIDI Remote Script/```](Ableton Live MIDI Remote Script/) contains a MIDI Remote Script for Ableton Live. The script maps the faders to control the volume of the first 8 tracks.  
Using this script is not necessary to use FDRbox in Live (or any other DAW that supports MIDI controllers), all it does is automatically map the controls for you.

To install the script, please refer to [ableton.com: How to install a third-party Remote Script?
](https://www.ableton.com/en/help/article/install-third-party-remote-script/)
