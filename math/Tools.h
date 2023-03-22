#ifndef TOOLS_H
#define TOOLS_H
#ifdef ASSERT
#include <assert.h>
#endif

#include <xmmintrin.h>
namespace sablin{

static const float FLOAT_ERROR = 10e-5;

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

}
#endif
