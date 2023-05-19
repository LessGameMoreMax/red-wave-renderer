#ifndef VERTEX_SHADE_H
#define VERTEX_SHADE_H
#include "Scene.h"
#include "Primitive.h"
namespace sablin{

class VertexShade{
public:
    static void* Transform(void*);
    static void PerVertexLight(Primitive*);
};
}
#endif
