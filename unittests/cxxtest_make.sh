#!/bin/bash

./cxxtest/cxxtestgen.py --error-printer -o runner.cpp check_adapter.h

g++ -ggdb2 -o runner \
	runner.cpp \
	../Adapter.cpp \
	-I . \
	-I .. \
	-I /usr/include \
	-lbluetooth

make_ret_code="$?"

if [ $make_ret_code -eq 0 ]; then
	./runner
fi
