
output: main.o list.o
	g++ main.o list.o -o output

main.o: main.cpp
	g++ -c main.cpp

list.o: list.cpp list.h
	g++ -c list.cpp

clean:
	rm *.o output
