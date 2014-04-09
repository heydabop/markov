CXX = g++
CXX_FLAGS = -std=c++11 -O2

all: 1-markov

#generic rule
%: %.cpp
	$(CXX) $(CXX_FLAGS) $@.cpp -o $@.out

clean:
	rm -f *.out
