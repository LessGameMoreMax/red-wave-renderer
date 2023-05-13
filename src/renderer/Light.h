#ifndef LIGHT_H
#define LIGHT_H
#include "../math/Vectors.h"
namespace sablin{
class Light{
protected:
    Vector4f world_position_;
    Vector4f color_;
public:
    Light(const Vector4f &world_position,
            const Vector4f &color);
    virtual Vector4f LightDirection(const Vector4f&) = 0;
    virtual Vector4f LightColor(const Vector4f&) = 0;
};
}
#endif
