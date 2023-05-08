#ifndef FRAGMENT_H
#define FRAGMENT_H
#include "Scene.h"
#include "../data/Material.h"
namespace sablin{
class Fragment{
public:
    Scene *scene_;
    
    Material *material_;
    Vector4f color_;
    
    float depth_;
    Vector4f world_coord_;
    Vector2f uv_coord_;
    Vector4f vertex_normal_;

    Vector2i screen_coord_;
};
}
#endif
