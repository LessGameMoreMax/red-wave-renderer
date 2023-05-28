#include "Texture.h"
namespace sablin{
Texture::Texture(const int32_t width, const int32_t height,
        Vector4f *texels): width_(width), height_(height),
        texels_(texels){}

Texture::~Texture(){
    if(texels_ != nullptr)
        delete[] texels_;
}

Vector4f Texture::Sample(const float u, const float v) const{
    int32_t real_u = u * width_;
    int32_t real_v = v * height_;
    return texels_[real_v * width_ + real_u];
}

Vector4f Texture::Sample(const Vector2f &uv) const{
    return Sample(uv.x_, uv.y_);
}

}
