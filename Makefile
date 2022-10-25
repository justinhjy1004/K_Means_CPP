CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic
DEPENDENCY = main.o kmeans.o parser.o writer.o

.PHONY: all
all: main

main: $(DEPENDENCY)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp parser.hpp kmeans.hpp

kmeans.o: kmeans.cpp kmeans.hpp

parser.o: parser.cpp parser.hpp

writer.o: writer.cpp parser.cpp

.PHONY: clean
clean:
	rm -rf main *.o