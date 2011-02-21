
CXXFLAGS := $(CXXFLAGS) -Wall
CXXFLAGS := $(CXXFLAGS) -I . -I /usr/include
LDFLAGS := $(LDFLAGS) -lbluetooth


#SIMPLE_SCAN_C := simplescan.c

BLUETOOTH_CPP := 	Adapter.cpp \
			Device.cpp \
			simplescan.cpp

simplescan: $(BLUETOOTH_CPP)
	g++ $(CXXFLAGS) -o $@ $(SIMPLE_SCAN_C) $(BLUETOOTH_CPP) $(LDFLAGS)

clean:
	rm -f *.o simplescan

tags: rebuild-tags

tags rebuild-tags:
	rm -rf tags ../tags */*/tags */tags
	ctags --exclude=*object* --exclude=*cscope* --tag-relative=no --recurse=yes .

extra-tags:
	ctags --tag-relative=no -a --recurse=yes /usr/include
	ctags --tag-relative=no -a --recurse=yes /usr/local/include

