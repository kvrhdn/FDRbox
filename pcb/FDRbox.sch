EESchema Schematic File Version 2
LIBS:FDRbox-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:PIC16F145x
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "FDRbox v0.1"
Date "2016-07-24"
Rev "v0.1"
Comp "Koenraad Verheyden"
Comment1 "@koenaad"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR01
U 1 1 5792220E
P 3100 2000
F 0 "#PWR01" H 3100 1850 50  0001 C CNN
F 1 "+5V" H 3100 2140 50  0000 C CNN
F 2 "" H 3100 2000 50  0000 C CNN
F 3 "" H 3100 2000 50  0000 C CNN
	1    3100 2000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 5792220F
P 5300 2000
F 0 "#PWR02" H 5300 1750 50  0001 C CNN
F 1 "GND" H 5300 1850 50  0000 C CNN
F 2 "" H 5300 2000 50  0000 C CNN
F 3 "" H 5300 2000 50  0000 C CNN
	1    5300 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3100 2000 3200 2000
Wire Wire Line
	5100 2000 5300 2000
Wire Wire Line
	3350 3100 3250 3100
Wire Wire Line
	3350 3200 3250 3200
Wire Wire Line
	2300 3300 3350 3300
Wire Wire Line
	2300 3000 3350 3000
$Comp
L GND #PWR03
U 1 1 57922210
P 2300 3300
F 0 "#PWR03" H 2300 3050 50  0001 C CNN
F 1 "GND" H 2300 3150 50  0000 C CNN
F 2 "" H 2300 3300 50  0000 C CNN
F 3 "" H 2300 3300 50  0000 C CNN
	1    2300 3300
	0    1    1    0   
$EndComp
$Comp
L +5V #PWR04
U 1 1 57922211
P 2300 3000
F 0 "#PWR04" H 2300 2850 50  0001 C CNN
F 1 "+5V" H 2300 3140 50  0000 C CNN
F 2 "" H 2300 3000 50  0000 C CNN
F 3 "" H 2300 3000 50  0000 C CNN
	1    2300 3000
	0    -1   -1   0   
$EndComp
Text Label 3250 3100 0    60   ~ 0
D-
Text Label 3250 3200 0    60   ~ 0
D+
Wire Wire Line
	5100 2100 5150 2100
Wire Wire Line
	5100 2200 5150 2200
Text Label 5150 2100 0    60   ~ 0
D+
Text Label 5150 2200 0    60   ~ 0
D-
$Comp
L C C4
U 1 1 57922212
P 5650 2300
F 0 "C4" H 5675 2400 50  0000 L CNN
F 1 "470nF" H 5675 2200 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 5688 2150 50  0001 C CNN
F 3 "" H 5650 2300 50  0000 C CNN
	1    5650 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 2300 5500 2300
Wire Wire Line
	5800 2300 5800 2300
$Comp
L GND #PWR05
U 1 1 57922213
P 5800 2300
F 0 "#PWR05" H 5800 2050 50  0001 C CNN
F 1 "GND" H 5800 2150 50  0000 C CNN
F 2 "" H 5800 2300 50  0000 C CNN
F 3 "" H 5800 2300 50  0000 C CNN
	1    5800 2300
	0    -1   -1   0   
$EndComp
$Comp
L C C3
U 1 1 57922214
P 3100 3150
F 0 "C3" H 3125 3250 50  0000 L CNN
F 1 "1µF" H 3125 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 3138 3000 50  0001 C CNN
F 3 "" H 3100 3150 50  0000 C CNN
	1    3100 3150
	-1   0    0    1   
$EndComp
Connection ~ 3100 3000
Connection ~ 3100 3300
Wire Wire Line
	3200 2300 3150 2300
Wire Wire Line
	4350 3000 4550 3000
Wire Wire Line
	4350 3100 4650 3100
Wire Wire Line
	4550 3200 4350 3200
Wire Wire Line
	4350 3300 4550 3300
Wire Wire Line
	4350 3400 4550 3400
Text Label 4550 3000 2    60   ~ 0
MCLR
$Comp
L +5V #PWR06
U 1 1 57922215
P 4650 3100
F 0 "#PWR06" H 4650 2950 50  0001 C CNN
F 1 "+5V" H 4650 3240 50  0000 C CNN
F 2 "" H 4650 3100 50  0000 C CNN
F 3 "" H 4650 3100 50  0000 C CNN
	1    4650 3100
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR07
U 1 1 57922216
P 4550 3200
F 0 "#PWR07" H 4550 2950 50  0001 C CNN
F 1 "GND" H 4550 3050 50  0000 C CNN
F 2 "" H 4550 3200 50  0000 C CNN
F 3 "" H 4550 3200 50  0000 C CNN
	1    4550 3200
	0    -1   1    0   
$EndComp
Text Label 4550 3300 2    60   ~ 0
RC0
Text Label 4550 3400 2    60   ~ 0
RC1
$Comp
L R R1
U 1 1 57922217
P 2750 2500
F 0 "R1" V 2830 2500 50  0000 C CNN
F 1 "150Ω" V 2750 2500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2680 2500 50  0001 C CNN
F 3 "" H 2750 2500 50  0000 C CNN
	1    2750 2500
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 57922218
P 2400 2500
F 0 "D1" H 2400 2600 50  0000 C CNN
F 1 "LED" H 2400 2400 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 2400 2500 50  0001 C CNN
F 3 "" H 2400 2500 50  0000 C CNN
	1    2400 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 57922219
P 2200 2500
F 0 "#PWR08" H 2200 2250 50  0001 C CNN
F 1 "GND" H 2200 2350 50  0000 C CNN
F 2 "" H 2200 2500 50  0000 C CNN
F 3 "" H 2200 2500 50  0000 C CNN
	1    2200 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	2200 2500 2200 2500
Wire Wire Line
	2600 2500 2600 2500
Wire Wire Line
	2900 2500 3200 2500
NoConn ~ 3750 3500
$Comp
L USB_B P1
U 1 1 5792221A
P 3650 3200
F 0 "P1" H 3850 3000 50  0000 C CNN
F 1 "USB_B" H 3600 3400 50  0000 C CNN
F 2 "Connect:USB_B" V 3600 3100 50  0001 C CNN
F 3 "" V 3600 3100 50  0000 C CNN
	1    3650 3200
	0    1    1    0   
$EndComp
$Comp
L CONN_01X05 P2
U 1 1 5792221B
P 4150 3200
F 0 "P2" H 4150 3500 50  0000 C CNN
F 1 "ICSP" V 4250 3200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 4150 3200 50  0001 C CNN
F 3 "" H 4150 3200 50  0000 C CNN
	1    4150 3200
	-1   0    0    -1  
$EndComp
$Comp
L PIC16F1455 U1
U 1 1 579223D3
P 4150 2300
F 0 "U1" H 4150 2200 50  0000 C CNN
F 1 "PIC16F1455" H 4150 2400 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-14_3.9x8.7mm_Pitch1.27mm" H 4150 2300 50  0001 C CNN
F 3 "DOCUMENTATION" H 4150 2300 50  0001 C CNN
	1    4150 2300
	1    0    0    -1  
$EndComp
Text Label 3150 2300 2    60   ~ 0
MCLR
Text Label 5150 2400 0    60   ~ 0
RC0
Text Label 5150 2500 0    60   ~ 0
RC1
Wire Wire Line
	5150 2500 5100 2500
Wire Wire Line
	5100 2400 5150 2400
$Comp
L 4051-RESCUE-FDRbox U2
U 1 1 57922ABA
P 6900 2600
F 0 "U2" H 7000 2600 50  0000 C CNN
F 1 "4051" H 7000 2400 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 6900 2600 60  0001 C CNN
F 3 "" H 6900 2600 60  0000 C CNN
	1    6900 2600
	-1   0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 57922B4B
P 6100 2800
F 0 "#PWR09" H 6100 2650 50  0001 C CNN
F 1 "+5V" H 6100 2940 50  0000 C CNN
F 2 "" H 6100 2800 50  0000 C CNN
F 3 "" H 6100 2800 50  0000 C CNN
	1    6100 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 57922B6E
P 6100 3200
F 0 "#PWR010" H 6100 2950 50  0001 C CNN
F 1 "GND" H 6100 3050 50  0000 C CNN
F 2 "" H 6100 3200 50  0000 C CNN
F 3 "" H 6100 3200 50  0000 C CNN
	1    6100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3100 6100 3100
Wire Wire Line
	6100 3000 6100 3200
Wire Wire Line
	6200 3000 6100 3000
Connection ~ 6100 3100
Wire Wire Line
	6200 2900 6100 2900
Wire Wire Line
	6100 2900 6100 2800
Wire Wire Line
	6200 2000 6150 2000
Wire Wire Line
	7600 2000 7650 2000
Wire Wire Line
	7600 2100 7650 2100
Wire Wire Line
	7600 2200 7650 2200
Wire Wire Line
	7600 2300 7650 2300
Wire Wire Line
	7600 2400 7650 2400
Wire Wire Line
	7650 2500 7600 2500
Wire Wire Line
	7600 2600 7650 2600
Wire Wire Line
	7650 2700 7600 2700
Wire Wire Line
	7600 2900 7900 2900
Wire Wire Line
	7600 3000 7650 3000
Wire Wire Line
	7600 3100 7650 3100
Wire Wire Line
	7650 3200 7600 3200
Text Label 6150 2000 2    60   ~ 0
FDR_X
Text Label 7650 2000 0    60   ~ 0
FDR_0
Text Label 7650 2100 0    60   ~ 0
FDR_1
Text Label 7650 2200 0    60   ~ 0
FDR_3
Text Label 7650 2300 0    60   ~ 0
FDR_2
Text Label 7650 2400 0    60   ~ 0
FDR_6
Text Label 7650 2500 0    60   ~ 0
FDR_7
Text Label 7650 2600 0    60   ~ 0
FDR_5
Text Label 7650 2700 0    60   ~ 0
FDR_4
Text Label 7650 3000 0    60   ~ 0
CH_0
Text Label 7650 3100 0    60   ~ 0
CH_1
Text Label 7650 3200 0    60   ~ 0
CH_2
$Comp
L GND #PWR011
U 1 1 579231EB
P 7900 2900
F 0 "#PWR011" H 7900 2650 50  0001 C CNN
F 1 "GND" H 7900 2750 50  0000 C CNN
F 2 "" H 7900 2900 50  0000 C CNN
F 3 "" H 7900 2900 50  0000 C CNN
	1    7900 2900
	0    -1   -1   0   
$EndComp
$Comp
L POT RV2
U 1 1 57937EB4
P 3400 4150
F 0 "RV2" H 3400 4070 50  0000 C CNN
F 1 "10k" H 3400 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 3400 4150 50  0001 C CNN
F 3 "" H 3400 4150 50  0000 C CNN
	1    3400 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3250 4150 3200 4150
Text Label 3200 4150 2    60   ~ 0
FDR_1
$Comp
L POT RV3
U 1 1 579381C9
P 4100 4150
F 0 "RV3" H 4100 4070 50  0000 C CNN
F 1 "10k" H 4100 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 4100 4150 50  0001 C CNN
F 3 "" H 4100 4150 50  0000 C CNN
	1    4100 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 4150 3900 4150
Text Label 3900 4150 2    60   ~ 0
FDR_2
$Comp
L POT RV4
U 1 1 57938271
P 4800 4150
F 0 "RV4" H 4800 4070 50  0000 C CNN
F 1 "10k" H 4800 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 4800 4150 50  0001 C CNN
F 3 "" H 4800 4150 50  0000 C CNN
	1    4800 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 4150 4600 4150
Text Label 4600 4150 2    60   ~ 0
FDR_3
$Comp
L POT RV5
U 1 1 57938279
P 5500 4150
F 0 "RV5" H 5500 4070 50  0000 C CNN
F 1 "10k" H 5500 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 5500 4150 50  0001 C CNN
F 3 "" H 5500 4150 50  0000 C CNN
	1    5500 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5350 4150 5300 4150
Text Label 5300 4150 2    60   ~ 0
FDR_4
$Comp
L POT RV6
U 1 1 579383AE
P 6200 4150
F 0 "RV6" H 6200 4070 50  0000 C CNN
F 1 "10k" H 6200 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 6200 4150 50  0001 C CNN
F 3 "" H 6200 4150 50  0000 C CNN
	1    6200 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6050 4150 6000 4150
Text Label 6000 4150 2    60   ~ 0
FDR_5
Text Label 6700 4150 2    60   ~ 0
FDR_6
Wire Wire Line
	7450 4150 7400 4150
Text Label 7400 4150 2    60   ~ 0
FDR_7
$Comp
L POT RV1
U 1 1 579383FB
P 2700 4150
F 0 "RV1" H 2700 4070 50  0000 C CNN
F 1 "10k" H 2700 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 2700 4150 50  0001 C CNN
F 3 "" H 2700 4150 50  0000 C CNN
	1    2700 4150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2550 4150 2500 4150
Text Label 2500 4150 2    60   ~ 0
FDR_0
Wire Wire Line
	2700 3800 2700 4000
Wire Wire Line
	2700 3900 7600 3900
Wire Wire Line
	3400 3900 3400 4000
Wire Wire Line
	4100 3900 4100 4000
Connection ~ 3400 3900
Wire Wire Line
	4800 3900 4800 4000
Connection ~ 4100 3900
Wire Wire Line
	5500 3900 5500 4000
Connection ~ 4800 3900
Wire Wire Line
	6200 3900 6200 4000
Connection ~ 5500 3900
Wire Wire Line
	6900 3900 6900 4000
Connection ~ 6200 3900
Wire Wire Line
	7600 3900 7600 4000
Connection ~ 6900 3900
Wire Wire Line
	7600 4400 7600 4300
Wire Wire Line
	2700 4400 7600 4400
Wire Wire Line
	6900 4400 6900 4300
Wire Wire Line
	6200 4400 6200 4300
Connection ~ 6900 4400
Wire Wire Line
	5500 4400 5500 4300
Connection ~ 6200 4400
Wire Wire Line
	4800 4300 4800 4400
Connection ~ 5500 4400
Wire Wire Line
	4100 4400 4100 4300
Connection ~ 4800 4400
Wire Wire Line
	3400 4400 3400 4300
Connection ~ 4100 4400
Wire Wire Line
	2700 4300 2700 4500
Connection ~ 3400 4400
Connection ~ 2700 3900
Connection ~ 2700 4400
$Comp
L GND #PWR012
U 1 1 57938AD6
P 2700 4500
F 0 "#PWR012" H 2700 4250 50  0001 C CNN
F 1 "GND" H 2700 4350 50  0000 C CNN
F 2 "" H 2700 4500 50  0000 C CNN
F 3 "" H 2700 4500 50  0000 C CNN
	1    2700 4500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR013
U 1 1 57938B18
P 2700 3800
F 0 "#PWR013" H 2700 3650 50  0001 C CNN
F 1 "+5V" H 2700 3940 50  0000 C CNN
F 2 "" H 2700 3800 50  0000 C CNN
F 3 "" H 2700 3800 50  0000 C CNN
	1    2700 3800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5100 2600 5150 2600
Text Label 5150 2600 0    60   ~ 0
FDR_X
$Comp
L C C2
U 1 1 57939526
P 2800 3150
F 0 "C2" H 2825 3250 50  0000 L CNN
F 1 "100nF" H 2825 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2838 3000 50  0001 C CNN
F 3 "" H 2800 3150 50  0000 C CNN
	1    2800 3150
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 57939569
P 2500 3150
F 0 "C1" H 2525 3250 50  0000 L CNN
F 1 "100nF" H 2525 3050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 2538 3000 50  0001 C CNN
F 3 "" H 2500 3150 50  0000 C CNN
	1    2500 3150
	-1   0    0    1   
$EndComp
Connection ~ 2500 3000
Connection ~ 2500 3300
Connection ~ 2800 3300
Connection ~ 2800 3000
Wire Wire Line
	3200 2600 3150 2600
Wire Wire Line
	3200 2400 3150 2400
Wire Wire Line
	3200 2200 3150 2200
NoConn ~ 3200 2100
Text Label 3150 2600 2    60   ~ 0
CH_2
Text Label 3150 2400 2    60   ~ 0
CH_1
Text Label 3150 2200 2    60   ~ 0
CH_0
Wire Wire Line
	6750 4150 6700 4150
$Comp
L POT RV7
U 1 1 5793D3F6
P 6900 4150
F 0 "RV7" H 6900 4070 50  0000 C CNN
F 1 "10k" H 6900 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 6900 4150 50  0001 C CNN
F 3 "" H 6900 4150 50  0000 C CNN
	1    6900 4150
	0    -1   -1   0   
$EndComp
$Comp
L POT RV8
U 1 1 5793D442
P 7600 4150
F 0 "RV8" H 7600 4070 50  0000 C CNN
F 1 "10k" H 7600 4150 50  0000 C CNN
F 2 "Bourns_PTA4543:PTA4543" H 7600 4150 50  0001 C CNN
F 3 "" H 7600 4150 50  0000 C CNN
	1    7600 4150
	0    -1   -1   0   
$EndComp
Text Notes 6800 1800 0    60   ~ 0
Faders are connected according to grey code.
$EndSCHEMATC
