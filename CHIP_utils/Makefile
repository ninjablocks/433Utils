CXX=arm-linux-gnueabihf-gcc

# Defines the GETCHIP variable which is needed by rc-switch/RCSwitch.h
CXXFLAGS=-DGETCHIP

all: send codesend RFSniffer

send: ../rc-switch/CHIP_IO/source/common.o ../rc-switch/CHIP_IO/source/event_gpio.o ../rc-switch/RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lpthread
	
codesend: ../rc-switch/CHIP_IO/source/common.o ../rc-switch/CHIP_IO/source/event_gpio.o ../rc-switch/RCSwitch.o codesend.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lpthread
	
RFSniffer: ../rc-switch/CHIP_IO/source/common.o ../rc-switch/CHIP_IO/source/event_gpio.o ../rc-switch/RCSwitch.o RFSniffer.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lpthread
	

clean:
	$(RM) ../rc-switch/CHIP_IO/source/*.o ../rc-switch/*.o *.o send codesend servo RFSniffer

