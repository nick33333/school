CXX = g++
CXXFLAGS = -Wall -std=c++11

sixdegrees: graph.o sixdegrees.o
	$(CXX) -g $(CXXFLAGS) -o sixdegrees graph.o sixdegrees.o
	
graph.o: graph.h graph.cpp
	$(CXX) -g $(CXXFLAGS) -c graph.cpp
	
sixdegrees.o: graph.cpp graph.h sixdegrees.cpp
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp
	
clean:
	rm -f *.o sixdegrees