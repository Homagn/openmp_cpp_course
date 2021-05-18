
output: main.o
	g++ main.o -o output -fopenmp

main.o: main.cpp
	g++ -c main.cpp -fopenmp

clean:
	rm *.o output
