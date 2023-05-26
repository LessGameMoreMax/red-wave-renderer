OBJ_S = main.o \
	    src/math/Compute.o \
		src/math/Matrixes.o \
        src/math/Tools.o \
		src/math/Vectors.o \
		src/sdl_display/Display.o \
		src/renderer/Frame.o \
		src/renderer/Object.o \
		src/renderer/Scene.o \
		src/renderer/Camera.o \
		src/renderer/Light.o \
		src/renderer/ParallelLight.o \
		src/renderer/Renderer.o \
		src/renderer/VertexShade.o \
		src/renderer/Clip.o \
		src/renderer/Rasterizer.o \
		src/renderer/FragmentShade.o \
		src/renderer/OutputMerger.o \
		src/driver/Loader.o \
		src/driver/PngLoader.o \
		src/data/Model.o \
		src/data/Material.o \
		src/data/Mesh.o \
		src/data/ModelPool.o \
		src/data/Texture.o \
		src/data/Triangle.o \
		src/data/Vertex.o \
		src/data/AABB.o

main : ${OBJ_S}
	g++ -Wall -o main.out $(OBJ_S) -lSDL2 -lpthread -lz

debug : ${OBJ_S}
	g++ -Wall -g -o main.out $(OBJ_S) -lSDL2 -lpthread -lz

$(OBJ_S) : $(HEADER_S)

.PHONY : clean
clean :
	rm main.out $(OBJ_S)
