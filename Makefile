CXX=clang++
CXXFLAGS=-std=c++20 -Wall -Werror -g

all : main

main : cell.o game.o main.o random.o action.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

%.o : %.cpp %.hpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f *.o main