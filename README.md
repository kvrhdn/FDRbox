PIC16F145x_MIDI
===
By Koenraad Verheyden - [@koenaad](https://twitter.com/koenaad)

Description
---
This project is meant to simplify designing USB MIDI controllers with the Microchip [PIC16F1454](http://www.microchip.com/wwwproducts/en/PIC16F1454) and [PIC16F1455](http://www.microchip.com/wwwproducts/en/PIC16F1455).

I chose for the PIC16F145x becaues it is the smallest MCU I found, capable of USB communication and that doesn't need an external oscillator. [The TSSOP-14 version is really small indeed...](http://i.imgur.com/X8IG8gG.jpg)  
Additionally, Microchip sells PDIP version which are rather pleasant to prototype with.

I made a small break-out board to experiment with this chip [[images](https://twitter.com/koenaad)]. If there is interest, I am willing to post the KiCad files online or ship some of my spare PCBs.  
I'm planning to use this project as base for other MIDI controllers I design.

Usage
---
The ```system```-functions handle device initialization, configuring the USB MIDI stack and LED updates. User code can be added in ```main.c```. Usually no other files should be edited for simple applications.  
Keep in mind that no code inside the main loop may block.

To program the PIC you will probably need a [PICkit](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=PG164130). Though, bootloaders could be an alternative.

MLA
---
This project uses the USB stack from [Microchip Libraries for Applications](http://microchip.com/mla).  
MLA is licensed under the Apache License version 2.0. (See: [microchip.com/mla_license](http://microchip.com/mla_license))
