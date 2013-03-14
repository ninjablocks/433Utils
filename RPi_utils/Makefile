all: send codesend servo

send: RCSwitch.o send.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi
	
codesend: RCSwitch.o codesend.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

servo: RCSwitch.o servo.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

clean:
	$(RM) *.o send codesend servo
