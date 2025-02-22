#ifndef TOOLS_H
#define TOOLS_H
#ifdef ASSERT
#include <assert.h>
#endif

#include "Vectors.h"
#include "Matrixes.h"
#include <xmmintrin.h>
#include "../data/AABB.h"
#include "../renderer/Primitive.h"
#include <cmath>
namespace sablin{

static const float FLOAT_ERROR = 10e-5;
static const float FLOAT_MAX = 10e35;
static const float FLOAT_MIN = -10e35;
static const int16_t INT16_T_MAX = 32700;
static const int16_t INT16_T_MIN = -32700;
static const double PI = std::acos(-1);

inline
constexpr float Abs(const float a){
    return ((a < 0)? -a : a);
}

inline
float Sqrt(const float a){
#ifdef ASSERT
    assert(a > 0);
#endif
    __m128 m_a = _mm_set1_ps(a);
    __m128 m_b = _mm_sqrt_ps(m_a);
    return m_b[0];
}

inline
float Rsqrt(const float a){
#ifdef ASSERT
    assert(a > FLOAT_ERROR);
#endif
    __m128 m_a = _mm_set1_ps(a);
    __m128 m_b = _mm_rsqrt_ps(m_a);
    return m_b[0];
}

inline
void Swap(float &a, float &b){
    float temp = a;
    a = b;
    b = temp;
}

inline
void Swap(int32_t &a, int32_t &b){
    int32_t temp = a;
    a = b;
    b = temp;
}

inline
double AngleToRadian(const float angle){
    return (double)angle / 180.0 * PI;
}

inline
float Saturate(float number){
    if(number < 0.0f) return 0.0f;
    if(number > 1.0f) return 1.0f;
    return number;
}

inline
void MemCopyRev(void *dist, void *src, size_t n){
    for(size_t i = 0,j = n-1;i != n; ++i, --j)
        ((char*)dist)[i] = ((char*)src)[j];
}

bool IsInFov(const AABB&, const Matrix4x4f&,
        const Matrix4x4f&, const Matrix4x4f&,
        const float, const float);

inline
int32_t Mask32(int32_t number){
    int32_t result = 1;
    return (result << number) - 1;
}

inline
int16_t Mask16(int16_t number){
    int16_t result = 1;
    return (result << number) - 1;
}

inline
int8_t Mask8(int8_t number){
    int8_t result = 1;
    return (result << number) - 1;
}

void BoundingBoxScreen(const Primitive*,Vector2i*,Vector2i*);
Matrix4x4f ShadowMatrix(const Vector3f &n, const Vector3f &l, 
            const float d, const bool is_point_light);

Vector3f LUPSolve3f(const Matrix3x3f&, const Matrix3x3f&, const Vector3i&, const Vector3f&);
Vector3i LUPDecomposition3x3f(Matrix3x3f&);
Vector4f LUPSolve4f(const Matrix4x4f&, const Matrix4x4f&, const Vector4i&, const Vector4f&);
Vector4i LUPDecomposition4x4f(Matrix4x4f&);

}
#endif
