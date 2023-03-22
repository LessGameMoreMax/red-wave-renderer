main: Vectors.o Matrixes.o main.o
	g++ -o main.out Vectors.o Matrixes.o main.o
main.o: main.cpp
	g++ -Wall -c main.cpp
Vectors.o: math/Vectors.cpp
	g++ -Wall -c math/Vectors.cpp
Matrixes.o: math/Matrixes.cpp
	g++ -Wall -c math/Matrixes.cpp
debug:
	g++ -Wall -g -c main.cpp
	g++ -Wall -g -c math/Vectors.cpp
	g++ -Wall -g -c math/Matrixes.cpp
	g++ -o main.out main.o Vectors.o Matrixes.cpp
clean:
	rm -rf main.out main.o *.o
