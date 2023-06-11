#include "Clip.h"
#include "Rasterizer.h"
namespace sablin{

void Clip::PrimitiveClip(Primitive *primitive){
//TODO: Implement primtive clip
    Rasterizer::PerspectiveDivide(primitive);
}
}
