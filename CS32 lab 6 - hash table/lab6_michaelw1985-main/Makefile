CXX = g++
#CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field


tests: tests.o WordCount.o tddFuncs.o
	$(CXX) $^ -o $@

tests.o: tests.cpp WordCount.h tddFuncs.h
	$(CXX) -c $^ 

WordCount.o: WordCount.h WordCount.cpp
	$(CXX) -c $^

tddFuncs.o: tddFuncs.h tddFuncs.cpp
	$(CXX) -c $^