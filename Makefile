
CXXFLAGS := $(CXXFLAGS) -Wall
CXXFLAGS := $(CXXFLAGS) -I .
LDFLAGS := $(LDFLAGS) -lbluetooth


SIMPLE_SCAN_C := simplescan.c

simplescan: $(SIMPLE_SCAN_C)
	gcc $(CXXFLAGS) -o $@ $(SIMPLE_SCAN_C) $(LDFLAGS)

clean:
	rm -f *.o simplescan
