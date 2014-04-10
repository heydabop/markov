CXX = g++
CXX_FLAGS = -std=c++11 -O2

all: 1-markov.out 2-markov.out

1-markov.out: 1-markov.cpp
	$(CXX) $(CXX_FLAGS) 1-markov.cpp -o 1-markov.out

2-markov.out: 2-markov.cpp
	$(CXX) $(CXX_FLAGS) 2-markov.cpp -o 2-markov.out

#generic rule
%: %.cpp
	$(CXX) $(CXX_FLAGS) $@.cpp -o $@.out

clean:
	rm -f *.out
