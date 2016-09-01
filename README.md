FDRbox
===
By Koenraad Verheyden - [@koenaad](https://twitter.com/koenaad)

Description
---
A barebones USB MIDI controller with 8 faders.

PCB
---
[```pcb/```](pcb/) contains the schematics and design of the PCB. The entire PCB was designed using [KiCad](http://kicad-pcb.org/), an open-source software suite for EDA.

PDF's of the schematic are placed in [```pcb/output/```](pcb/output/).

Code
---
[```code/```](code/) is a subtree of [PIC16F145x_MIDI](https://github.com/koenaad/PIC16F145x_MIDI). Most controller specific code is in [```main.c```](code/main.c).

This project uses the USB stack from [Microchip Libraries for Applications](http://microchip.com/mla).  
MLA is licensed under the Apache License version 2.0. (See: [microchip.com/mla_license](http://microchip.com/mla_license))


Ableton Live MIDI Remote Script
---
[```Ableton Live MIDI Remote Script/```](Ableton Live MIDI Remote Script/) contains a MIDI Remote Script for Ableton Live. The script maps the faders to control the volume of the first 8 tracks. Using this script is not necessary to use FDRbox in Live (or any other DAW that support MIDI controllers), all it does it automatically map the controls.

To install the script, please refer to [ableton.com: How to install a third-party Remote Script?
](https://www.ableton.com/en/help/article/install-third-party-remote-script/)
