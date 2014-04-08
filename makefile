CXX = g++
CXX_FLAGS = -std=c++11 -O1

all: main

#generic rule
%: %.cpp
	$(CXX) $(CXX_FLAGS) $@.cpp -o $@.out

clean:
	rm -f *.out
