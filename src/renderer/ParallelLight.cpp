#include "ParallelLight.h"
namespace sablin{
ParallelLight::ParallelLight(const Vector4f &direction,
        const Vector4f &color):Light(Vector4f(), color){
    direction_.x_ = -direction.x_;
    direction_.y_ = -direction.y_;
    direction_.z_ = -direction.z_;
    direction_.w_ = 0.0f;
    direction_.Normalized();
}

Vector4f ParallelLight::LightDirection(const Vector4f &position){
    return direction_;
}

Vector4f ParallelLight::LightColor(const Vector4f &position){
    return color_;
}
}
