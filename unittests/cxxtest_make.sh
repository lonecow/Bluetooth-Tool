#!/bin/bash

./cxxtest/cxxtestgen.py --error-printer -o runner.cpp check_*.h

g++ -ggdb2 -o runner \
	runner.cpp \
	../Adapter.cpp \
	../Device.cpp \
	-I . \
	-I .. \
	-I /usr/include \
	-lbluetooth

make_ret_code="$?"

if [ $make_ret_code -eq 0 ]; then
	valgrind --leak-check=full -q --num-callers=40 ./runner
fi
