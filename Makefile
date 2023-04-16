OBJ_S = main.o \
	    math/Compute.o \
		math/Matrixes.o \
        math/Tools.o \
		math/Vectors.o

main : ${OBJ_S}
	g++ -Wall -o main.out $(OBJ_S) -lSDL2

$(OBJ_S) : $(HEADER_S)

.PHONY : clean
clean :
	rm main.out $(OBJ_S)
