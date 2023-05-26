#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdint.h>
#include "../math/Vectors.h"
namespace sablin{

class Texture{
private:
    int32_t width_;
    int32_t height_;
    Vector4f *texels_;
public:
    explicit Texture(const int32_t, const int32_t,
            Vector4f*);
    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;
    ~Texture();

    Vector4f Sample(const float, const float) const;
};
}
#endif
