#ifndef VECTORS_H
#define VECTORS_H
#include <cstdint>
#include <xmmintrin.h>
namespace sablin{

class Vector3f{
public:
    union{
        struct{
            float x_ = 0.0f;
            float y_ = 0.0f;
            float z_ = 0.0f;
        };
        float s_[3];
    };
public:
    explicit Vector3f(): x_(0.0f), y_(0.0f), z_(0.0f){}
    explicit Vector3f(float x, float y, float z);
    Vector3f(const Vector3f&) = default;
    Vector3f(Vector3f&&) = default;
    Vector3f& operator=(const Vector3f&) = default;
    Vector3f& operator=(Vector3f&&) = default;
    ~Vector3f() = default;

    Vector3f& operator+=(const Vector3f&);
    Vector3f& operator+=(const float);
    Vector3f& operator-=(const Vector3f&);
    Vector3f& operator-=(const float);
    Vector3f& operator*=(const float);
    Vector3f& operator/=(const float);

    float Norm() const;
    Vector3f Normalized();
}__attribute__((aligned(16))); // explicitly align for 16 byte

Vector3f operator+(const Vector3f&, const Vector3f&);
Vector3f operator-(const Vector3f&, const Vector3f&);
Vector3f operator+(const Vector3f&, const float);
Vector3f operator-(const Vector3f&, const float);
Vector3f operator*(const Vector3f&, const float);
Vector3f operator*(const Vector3f&, const Vector3f&);
Vector3f operator/(const Vector3f&, const float);
bool     operator==(const Vector3f&, const Vector3f&);
bool     operator!=(const Vector3f&, const Vector3f&);

class Vector4f{
public:
    union{
        struct{
            float x_ = 0.0f;
            float y_ = 0.0f;
            float z_ = 0.0f;
            float w_ = 0.0f;
        };
        float s_[4];
        __m128 v_;
    };

    explicit Vector4f(): x_(0.0f), y_(0.0f), z_(0.0f), w_(0.0f){}
    explicit Vector4f(float x, float y, float z, float w);
    explicit Vector4f(__m128 v);
    explicit Vector4f(const Vector3f&, float w);
    Vector4f(const Vector4f&) = default;
    Vector4f(Vector4f&&) = default;
    Vector4f& operator=(const Vector4f&) = default;
    Vector4f& operator=(Vector4f&&) = default;
    ~Vector4f() = default;

    Vector4f& operator+=(const Vector4f&);
    Vector4f& operator+=(const float);
    Vector4f& operator-=(const Vector4f&);
    Vector4f& operator-=(const float);
    Vector4f& operator*=(const float);
    Vector4f& operator/=(const float);

    float Norm() const;
    Vector4f Normalized();
}__attribute__((aligned(16))); // explicitly align for 16 byte

Vector4f operator+(const Vector4f&, const Vector4f&);
Vector4f operator-(const Vector4f&, const Vector4f&);
Vector4f operator+(const Vector4f&, const float);
Vector4f operator-(const Vector4f&, const float);
Vector4f operator*(const Vector4f&, const float);
Vector4f operator*(const Vector4f&, const Vector4f&);
Vector4f operator/(const Vector4f&, const float);
bool     operator==(const Vector4f&, const Vector4f&);
bool     operator!=(const Vector4f&, const Vector4f&);

class Vector3i{
public:
    union{
        struct{
            int32_t x_ = 0;
            int32_t y_ = 0;
            int32_t z_ = 0;
        };
        int32_t s_[3];
    };
public:
    explicit Vector3i(): x_(0.0f), y_(0.0f), z_(0.0f){}
    explicit Vector3i(int32_t x, int32_t y, int32_t z);
    Vector3i(const Vector3i&) = default;
    Vector3i(Vector3i&&) = default;
    Vector3i& operator=(const Vector3i&) = default;
    Vector3i& operator=(Vector3i&&) = default;
    ~Vector3i() = default;

    Vector3i& operator+=(const Vector3i&);
    Vector3i& operator+=(const int32_t);
    Vector3i& operator-=(const Vector3i&);
    Vector3i& operator-=(const int32_t);

    float Norm() const;
}__attribute__((aligned(16))); // explicitly align for 16 byte

Vector3i operator+(const Vector3i&, const Vector3i&);
Vector3i operator-(const Vector3i&, const Vector3i&);
Vector3i operator+(const Vector3i&, const int32_t);
Vector3i operator-(const Vector3i&, const int32_t);
bool     operator==(const Vector3i&, const Vector3i&);
bool     operator!=(const Vector3i&, const Vector3i&);

class Vector4i{
public:
    union{
        struct{
            int32_t x_ = 0;
            int32_t y_ = 0;
            int32_t z_ = 0;
            int32_t w_ = 0;
        };
        int32_t s_[4];
    };

    explicit Vector4i(): x_(0), y_(0), z_(0), w_(0){}
    explicit Vector4i(int32_t x, int32_t y, int32_t z, int32_t w);
    Vector4i(const Vector4i&) = default;
    Vector4i(Vector4i&&) = default;
    Vector4i& operator=(const Vector4i&) = default;
    Vector4i& operator=(Vector4i&&) = default;
    ~Vector4i() = default;

    Vector4i& operator+=(const Vector4i&);
    Vector4i& operator+=(const int32_t);
    Vector4i& operator-=(const Vector4i&);
    Vector4i& operator-=(const int32_t);

    float Norm() const;
}__attribute__((aligned(16))); // explicitly align for 16 byte

Vector4i operator+(const Vector4i&, const Vector4i&);
Vector4i operator-(const Vector4i&, const Vector4i&);
Vector4i operator+(const Vector4i&, const int32_t);
Vector4i operator-(const Vector4i&, const int32_t);
bool     operator==(const Vector4i&, const Vector4i&);
bool     operator!=(const Vector4i&, const Vector4i&);

class Vector2f{
public:
    union{
        struct{
            float x_ = 0.0f;
            float y_ = 0.0f;
        };
        float s_[2];
    };
public:
    explicit Vector2f(): x_(0.0f), y_(0.0f){}
    explicit Vector2f(float x, float y);
    Vector2f(const Vector2f&) = default;
    Vector2f(Vector2f&&) = default;
    Vector2f& operator=(const Vector2f&) = default;
    Vector2f& operator=(Vector2f&&) = default;
    ~Vector2f() = default;

    Vector2f& operator+=(const Vector2f&);
    Vector2f& operator+=(const float);
    Vector2f& operator-=(const Vector2f&);
    Vector2f& operator-=(const float);
    Vector2f& operator*=(const float);
    Vector2f& operator/=(const float);

}__attribute__((aligned(16))); // explicitly align for 16 byte

Vector2f operator+(const Vector2f&, const Vector2f&);
Vector2f operator-(const Vector2f&, const Vector2f&);
Vector2f operator+(const Vector2f&, const float);
Vector2f operator-(const Vector2f&, const float);
Vector2f operator*(const Vector2f&, const float);
Vector2f operator/(const Vector2f&, const float);
bool     operator==(const Vector2f&, const Vector2f&);
bool     operator!=(const Vector2f&, const Vector2f&);

class Vector2i{
public:
    union{
        struct{
            int32_t x_ = 0.0f;
            int32_t y_ = 0.0f;
        };
        int32_t s_[2];
    };
public:
    explicit Vector2i(): x_(0), y_(0){}
    explicit Vector2i(int32_t x, int32_t y);
    Vector2i(const Vector2i&) = default;
    Vector2i(Vector2i&&) = default;
    Vector2i& operator=(const Vector2i&) = default;
    Vector2i& operator=(Vector2i&&) = default;
    ~Vector2i() = default;

    Vector2i& operator+=(const Vector2i&);
    Vector2i& operator+=(const int32_t);
    Vector2i& operator-=(const Vector2i&);
    Vector2i& operator-=(const int32_t);
    Vector2i& operator*=(const int32_t);
    Vector2i& operator/=(const int32_t);

}__attribute__((aligned(16))); // explicitly align for 16 byte

Vector2i operator+(const Vector2i&, const Vector2i&);
Vector2i operator-(const Vector2i&, const Vector2i&);
Vector2i operator+(const Vector2i&, const int32_t);
Vector2i operator-(const Vector2i&, const int32_t);
Vector2i operator*(const Vector2i&, const int32_t);
Vector2i operator/(const Vector2i&, const int32_t);
bool     operator==(const Vector2i&, const Vector2i&);
bool     operator!=(const Vector2i&, const Vector2i&);
}
#endif
