EESchema Schematic File Version 2
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
LIBS:components
LIBS:audio_controller_teensy
EELAYER 25 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "audio_controller_teensy"
Date ""
Rev "1.0"
Comp "Janelia"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR01
U 1 1 577150E0
P 900 1000
F 0 "#PWR01" H 900 750 50  0001 C CNN
F 1 "GND" H 905 827 50  0000 C CNN
F 2 "" H 900 1000 50  0000 C CNN
F 3 "" H 900 1000 50  0000 C CNN
	1    900  1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  1000 900  950 
Wire Wire Line
	700  950  1350 950 
NoConn ~ 3850 850 
NoConn ~ 3850 1050
NoConn ~ 1350 1050
NoConn ~ 1350 1450
NoConn ~ 1350 1550
NoConn ~ 1350 1750
NoConn ~ 1350 1850
NoConn ~ 3850 1450
NoConn ~ 3850 1550
NoConn ~ 3850 1850
NoConn ~ 3850 1950
NoConn ~ 3850 2050
NoConn ~ 1350 1150
$Comp
L PWR_FLAG #FLG012
U 1 1 578F91CB
P 700 900
F 0 "#FLG012" H 700 995 50  0001 C CNN
F 1 "PWR_FLAG" H 700 1124 50  0000 C CNN
F 2 "" H 700 900 50  0000 C CNN
F 3 "" H 700 900 50  0000 C CNN
	1    700  900 
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG013
U 1 1 578F9241
P 4300 1050
F 0 "#FLG013" H 4300 1145 50  0001 C CNN
F 1 "PWR_FLAG" H 4300 1274 50  0000 C CNN
F 2 "" H 4300 1050 50  0000 C CNN
F 3 "" H 4300 1050 50  0000 C CNN
	1    4300 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  900  700  950 
Connection ~ 900  950 
$Comp
L MODULAR_DEVICE_TEENSY_MALE MDT1
U 1 1 57A8C92C
P 2600 1600
F 0 "MDT1" H 2600 2597 60  0000 C CNN
F 1 "MODULAR_DEVICE_TEENSY_MALE" H 2600 2491 60  0000 C CNN
F 2 "audio_controller_teensy:MODULAR_DEVICE_TEENSY_MALE" H 2600 2650 60  0001 C CNN
F 3 "" H 2650 4350 60  0000 C CNN
F 4 "digikey" H 2600 2750 60  0001 C CNN "Vendor"
F 5 "S1011E-16-ND" H 2600 2850 60  0001 C CNN "PartNumber"
F 6 "16 Position Header Through Hole Male Pins" H 2600 2950 60  0001 C CNN "Description"
F 7 "2" H 3900 2850 60  0001 C CNN "PartCount"
	1    2600 1600
	1    0    0    -1  
$EndComp
NoConn ~ 1350 1350
NoConn ~ 1350 1250
Wire Wire Line
	3850 1750 3950 1750
Text Label 3950 1750 0    60   ~ 0
SDA
Wire Wire Line
	3850 1650 3950 1650
Text Label 3950 1650 0    60   ~ 0
SCL
Wire Wire Line
	1350 2150 1050 2150
Text Label 1050 2350 0    60   ~ 0
MCLK
Wire Wire Line
	1350 1950 1050 1950
Text Label 1050 1950 0    60   ~ 0
BCLK
Wire Wire Line
	3850 1250 3950 1250
Text Label 3950 1250 0    60   ~ 0
LRCLK
Wire Wire Line
	3850 1350 3950 1350
Text Label 3950 1350 0    60   ~ 0
I2STX
Wire Wire Line
	3850 2250 3950 2250
Text Label 3950 2250 0    60   ~ 0
I2SRX
NoConn ~ 3850 950 
NoConn ~ 1350 850 
Wire Wire Line
	1350 2250 1050 2250
Text Label 1050 2250 0    60   ~ 0
MISO
Wire Wire Line
	1350 2050 1050 2050
Text Label 1050 2050 0    60   ~ 0
SDCS
Text Label 1050 2150 0    60   ~ 0
MOSI
Wire Wire Line
	1350 2350 1050 2350
Wire Wire Line
	3850 2150 3950 2150
Text Label 3950 2150 0    60   ~ 0
SCK
Wire Wire Line
	1350 1650 950  1650
Text Label 950  1650 0    60   ~ 0
MEMCS
$Comp
L +3V3 #PWR?
U 1 1 57C71ADB
P 4000 1050
F 0 "#PWR?" H 4000 900 50  0001 C CNN
F 1 "+3V3" H 4015 1223 50  0000 C CNN
F 2 "" H 4000 1050 50  0000 C CNN
F 3 "" H 4000 1050 50  0000 C CNN
	1    4000 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1050 4300 1150
Wire Wire Line
	4300 1150 3850 1150
Wire Wire Line
	4000 1050 4000 1150
Connection ~ 4000 1150
Wire Wire Line
	3850 2350 3950 2350
Text Label 3950 2350 0    60   ~ 0
DAC
$Comp
L SGTL5000 U?
U 1 1 57C89602
P 7350 2300
F 0 "U?" H 7800 3000 60  0000 C CNN
F 1 "SGTL5000" H 6950 3000 60  0000 C CNN
F 2 "footprints:QFN-5x5-32" H 7650 2900 60  0001 C CNN
F 3 "" H 7350 2300 60  0001 C CNN
F 4 "digikey" H 7850 3100 60  0001 C CNN "Vendor"
F 5 "SGTL5000XNAA3R2CT-ND" H 7950 3200 60  0001 C CNN "PartNumber"
F 6 "Stereo Audio Interface 32-QFN" H 8050 3300 60  0001 C CNN "Description"
	1    7350 2300
	1    0    0    -1  
$EndComp
$Comp
L AP7313_1.5V U?
U 1 1 57C8ABBD
P 2400 3600
F 0 "U?" H 2400 3847 60  0000 C CNN
F 1 "AP7313_1.5V" H 2400 3741 60  0000 C CNN
F 2 "footprints:SOT-23-3" H 2450 3300 60  0001 C CNN
F 3 "" H 2400 3600 60  0001 C CNN
F 4 "digikey" H 2650 3500 60  0001 C CNN "Vendor"
F 5 "AP7313-15SAG-7DICT-ND" H 2750 3600 60  0001 C CNN "PartNumber"
F 6 "Linear Voltage Regulator IC Positive Fixed 1 Output 1.5V 150mA SOT-23-3" H 2850 3700 60  0001 C CNN "Description"
	1    2400 3600
	1    0    0    -1  
$EndComp
$Comp
L 2.2uF C?
U 1 1 57C8D133
P 1600 3850
F 0 "C?" H 1650 3950 40  0000 L CNN
F 1 "2.2uF" H 1600 3850 30  0000 C CNN
F 2 "footprints:SM1210" H 1638 3700 30  0001 C CNN
F 3 "" H 1600 3850 60  0000 C CNN
F 4 "digikey" H 1700 4050 60  0001 C CNN "Vendor"
F 5 "478-3591-1-ND" H 1800 4150 60  0001 C CNN "PartNumber"
F 6 "2.2uF 50V Ceramic Capacitor X7R 1210" H 1900 4250 60  0001 C CNN "Description"
	1    1600 3850
	1    0    0    -1  
$EndComp
$Comp
L 0.1uF C?
U 1 1 57C8D1F2
P 1800 3850
F 0 "C?" H 1850 3950 40  0000 L CNN
F 1 "0.1uF" H 1800 3850 30  0000 C CNN
F 2 "footprints:SM1210" H 1838 3700 30  0001 C CNN
F 3 "" H 1800 3850 60  0000 C CNN
F 4 "digikey" H 1900 4050 60  0001 C CNN "Vendor"
F 5 "478-3586-1-ND" H 2000 4150 60  0001 C CNN "PartNumber"
F 6 "CAP CER 0.1UF 50V 10% X7R 1210" H 2100 4250 60  0001 C CNN "Description"
	1    1800 3850
	1    0    0    -1  
$EndComp
$Comp
L 0.1uF C?
U 1 1 57C8D519
P 2000 3850
F 0 "C?" H 2050 3950 40  0000 L CNN
F 1 "0.1uF" H 2000 3850 30  0000 C CNN
F 2 "footprints:SM1210" H 2038 3700 30  0001 C CNN
F 3 "" H 2000 3850 60  0000 C CNN
F 4 "digikey" H 2100 4050 60  0001 C CNN "Vendor"
F 5 "478-3586-1-ND" H 2200 4150 60  0001 C CNN "PartNumber"
F 6 "CAP CER 0.1UF 50V 10% X7R 1210" H 2300 4250 60  0001 C CNN "Description"
	1    2000 3850
	1    0    0    -1  
$EndComp
$Comp
L 2.2uF C?
U 1 1 57C8D5F7
P 2900 3850
F 0 "C?" H 2950 3950 40  0000 L CNN
F 1 "2.2uF" H 2900 3850 30  0000 C CNN
F 2 "footprints:SM1210" H 2938 3700 30  0001 C CNN
F 3 "" H 2900 3850 60  0000 C CNN
F 4 "digikey" H 3000 4050 60  0001 C CNN "Vendor"
F 5 "478-3591-1-ND" H 3100 4150 60  0001 C CNN "PartNumber"
F 6 "2.2uF 50V Ceramic Capacitor X7R 1210" H 3200 4250 60  0001 C CNN "Description"
	1    2900 3850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
