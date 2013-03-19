# About

rcswitch-pi is for controlling rc remote controlled power sockets 
with the raspberry pi. Kudos to the projects [rc-switch](http://code.google.com/p/rc-switch)
and [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi).
I just adapted the rc-switch code to use the wiringpi library instead of
the library provided by the arduino.


## Usage

First you have to install the [wiringpi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) library.
After that you can compile the example program *send* by executing *make*. 
You may want to change the used GPIO pin before compilation of the codesend.cpp source file.

## Note
The 'RF\_Sniffer' code is as yet untested.  It _should_ work, but it is still being tested thoroughly.  It's provided to allow you to start playing with it now.
