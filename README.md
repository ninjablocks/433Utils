# About 433Utils

433Utils is a collection of code and documentation designed to assist you in the connection and usage of RF 433MHz transmit and receive modules to/with your Arduino and Rapberry Pi.

It consists of two main sections- Arduino sketches and Raspberry Pi command line utilities.  You'll find those in appropriately named folders.

Despite the name, 433Utils also works with 315MHz transmit and receive modules (tested).

## Requirements

1. An Arduino (two is ideal)
2. A Raspberry Pi
3. The git commandline tool, on both your Arduino IDE machine and your RPi
4. RF 433MHz modules; a transmitter and receiver
5. A Ninja Block and account

## Installation

### Arduino\_Sketches

Place the Sketches in your normal Arduino Sketches location.  Install any required libraries:

1. Servo motor library (Should be included in the Arduino IDE)
2. _Arduino_ [rc_switch](http://code.google.com/p/rc-switch/) library

### RPi\_utils

From your RPi, clone this archive:

1. ```git clone --recursive git://github.com/ninjablocks/433Utils.git``` (recursive ensure that the rc-switch submodule gets populated which is needed by RPi\_utils)

2. ```cd 433Utils/RPi_utils```

3. (As per the original rc_switch distribution) Follow the instructions to install the  [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) library.
After that you can compile the example programs by executing *make*. 

## Usage

### send 
```sudo ./send systemCode unitCode command```

This command is unaltered from the original rc\_switch distribution.


### codesend 
```sudo ./codesend decimalcode```

This command uses a single Ninja Blocks compatible decimal code.  Sniff out codes using the RF\_Sniffer.ino Arduino sketch, included in this distribution.

You can use codesend to control the wireless servo on your Arduino.
(The sketch is Servo\_Receive\_Demo.ino)

I've implemented the most bare-bones of controls here.  Try:

```sudo ./codesend 500000 # to move the servo up```

```sudo ./codesend 500001 # to move the servo down```

```sudo ./codesend 500002 # to move the servo left```

```sudo ./codesend 500003 # to move the servo right```

```sudo ./codesend 500004 # to move the servo home```

## Issues

Due to limitiations in the implementation of interrupt-driven routines in the underlying RCSwitch library, it is currently not possible to use both the send and receive functionality within the one program.  
