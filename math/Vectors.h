#ifndef VECTORS_H
#define VECTORS_H
namespace sablin{

class Vector3f{
public:
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;

    explicit Vector3f() = default;
    explicit Vector3f(float x, float y, float z);
    Vector3f(const Vector3f&) = default;
    Vector3f(Vector3f&&) = default;
    Vector3f& operator=(const Vector3f&) = default;
    Vector3f& operator=(Vector3f&&) = default;
    ~Vector3f() = default;
};

class Vector4f{
public:
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;
    float w_ = 0.0f;

    explicit Vector4f() = default;
    explicit Vector4f(float x, float y, float z, float w);
    Vector4f(const Vector4f&) = default;
    Vector4f(Vector4f&&) = default;
    Vector4f& operator=(const Vector4f&) = default;
    Vector4f& operator=(Vector4f&&) = default;
    ~Vector4f() = default;
};

}
#endif
