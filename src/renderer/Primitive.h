#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include "Scene.h"
#include "../data/Material.h"
namespace sablin{
class Primitive{
public:
    Scene *scene_;
    Object *object_;

    Material *material_;
    Vector4f plane_normal_;

    Vector4f world_coord_[3];
    Vector4f project_coord_[3];
    Vector2f uv_coord_[3];
    Vector4f vertex_normal_[3];
};
}
#endif
