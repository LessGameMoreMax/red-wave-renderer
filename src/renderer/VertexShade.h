#ifndef VERTEX_SHADE_H
#define VERTEX_SHADE_H
#include "Scene.h"
#include "Primitive.h"
namespace sablin{

class VertexShade{
public:
    static void Transform(Scene*, const int32_t, const int32_t, Object*,
            const Matrix4x4f&, const Matrix4x4f&, const Matrix4x4f&);
    static void PerVertexLight(Primitive*);
};
}
#endif
