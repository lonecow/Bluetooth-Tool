
CXXFLAGS := $(CXXFLAGS) -Wall
CXXFLAGS := $(CXXFLAGS) -I .
LDFLAGS := $(LDFLAGS) -lbluetooth


SIMPLE_SCAN_C := simplescan.c

simplescan: $(SIMPLE_SCAN_C)
	gcc $(CXXFLAGS) -o $@ $(SIMPLE_SCAN_C) $(LDFLAGS)

clean:
	rm -f *.o simplescan

tags: rebuild-tags

tags rebuild-tags:
	rm -rf tags ../tags */*/tags */tags
	ctags --exclude=*object* --exclude=*cscope* --tag-relative=no --recurse=yes .

extra-tags:
	ctags --tag-relative=no -a --recurse=yes /usr/include
	ctags --tag-relative=no -a --recurse=yes /usr/local/include

