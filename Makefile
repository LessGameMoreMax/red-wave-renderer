main: Vectors.o Matrixes.o Compute.o main.o Tools.o
	g++ -o main.out Vectors.o Matrixes.o Compute.o main.o Tools.o
main.o: main.cpp
	g++ -Wall -c main.cpp
Vectors.o: math/Vectors.cpp
	g++ -Wall -c math/Vectors.cpp
Matrixes.o: math/Matrixes.cpp
	g++ -Wall -c math/Matrixes.cpp
Compute.o: math/Compute.cpp
	g++ -Wall -c math/Compute.cpp
Tools.o: math/Tools.cpp
	g++ -Wall -c math/Tools.cpp
debug:
	g++ -Wall -g -c main.cpp
	g++ -Wall -g -c math/Vectors.cpp
	g++ -Wall -g -c math/Matrixes.cpp
	g++ -Wall -g -c math/Compute.cpp
	g++ -Wall -g -c math/Tools.cpp
	g++ -o main.out main.o Vectors.o Matrixes.o Compute.o Tools.o
clean:
	rm -rf main.out main.o *.o
