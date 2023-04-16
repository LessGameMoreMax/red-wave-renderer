OBJ_S = main.o \
	    src/math/Compute.o \
		src/math/Matrixes.o \
        src/math/Tools.o \
		src/math/Vectors.o \
		src/sdl_display/Display.o

main : ${OBJ_S}
	g++ -Wall -o main.out $(OBJ_S) -lSDL2

$(OBJ_S) : $(HEADER_S)

.PHONY : clean
clean :
	rm main.out $(OBJ_S)
