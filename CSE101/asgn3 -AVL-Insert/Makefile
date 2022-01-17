CXX = g++
CXXFLAGS = -Wall -std=c++11

main: avl.o main.o
	$(CXX) -g $(CXXFLAGS) -o main avl.o main.o

avl.o: avl.cpp
	$(CXX) -g $(CXXFLAGS) -c avl.cpp

main.o: main.cpp avl.h avl.cpp
	$(CXX) -g $(CXXFLAGS) -c avl.cpp main.cpp

clean: 
	rm *.o main
