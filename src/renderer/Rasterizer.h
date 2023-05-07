#ifndef RASTERIZER_H
#define RASTERIZER_H
#include "Primitive.h"
namespace sablin{
class Rasterizer{
public:
    static void PerspectiveDivide(Primitive*);
    static void ViewportTransform(Primitive*);
    static void BackfaceCulling(Primitive*);
};
}
#endif
