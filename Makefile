main: Vectors.o main.o
	g++ -o main.out Vectors.o main.o
main.o: main.cpp
	g++ -Wall -c main.cpp
Vectors.o: math/Vectors.cpp
	g++ -Wall -c math/Vectors.cpp
debug:
	g++ -Wall -g -c main.cpp
	g++ -Wall -g -c math/Vectors.cpp
	g++ -o main.out main.o Vectors.o
clean:
	rm -rf main.out main.o *.o
