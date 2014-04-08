CXX = g++
CXX_FLAGS = -std=c++11 -O2

all: main

#generic rule
%: %.cpp
	$(CXX) $(CXX_FLAGS) $@.cpp -o $@.out

clean:
	rm -f *.out
