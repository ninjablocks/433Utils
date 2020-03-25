/*
   RFSniffer

Usage: ./RFSniffer [<pulseLength>]
[] = optional

Hacked from http://code.google.com/p/rc-switch/
by @justy to provide a handy RF code sniffer
Adapted by korfhage(dot)michel(at)web(dot)de
 */

#include <cstdlib>
#include <cerrno>

#include <string>
#include <iostream>

#include <unistd.h>

#include "../rc-switch/RCSwitch.h"

using std::cout;
using std::endl;

// This pin is not the first pin on the RPi GPIO header!
// Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
// for more information.
constexpr int PIN = 2;

template<class dest>
dest cast(char* param, unsigned int& errorCode)
{
	char* end;
	errno = 0;
	long l = std::strtol(param, &end, 10); 	
	cout << "set pulse length to " << l << endl;
	dest ret(l);
	if(errno || ret != l) errorCode = errno;
	return ret;
}

int main(int argc, char *argv[]) {
	if(wiringPiSetup() == -1) {
		cout << "wiringPiSetup failed, exiting..." << endl;
		return 101;
	}

	RCSwitch mySwitch;

	if(argv[1])
	{
		unsigned int error = 0;
		// first argument will parsed as the pulselength
		int pulseLength = cast<int>(argv[1], error);
		if(error)
		{
			cout << "invalid first argument! needs to be signed number." << endl;
			return 102;
		}
		if (pulseLength) mySwitch.setPulseLength(pulseLength);
	}

	mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2

	while(1) {
		if (mySwitch.available()) {
			auto value = mySwitch.getReceivedValue();
			if (!value) {
				cout << "Unknown encoding";
			} else {    
				cout << "Received " << value;
			}
			cout << endl;
			mySwitch.resetAvailable();
		}
		usleep(100); 

	}
	return 0;
}

