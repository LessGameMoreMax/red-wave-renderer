#include "Compute.h"
#include "Tools.h"
#include <xmmintrin.h>
namespace sablin{

float DotProduct(const Vector3f &rhs, const Vector3f &lhs){
    return rhs.x_*lhs.x_+rhs.y_*lhs.y_+rhs.z_*lhs.z_;
}

Vector3f CrossProduct(const Vector3f &rhs, const Vector3f &lhs){
    return Vector3f(rhs.y_*lhs.z_-rhs.z_*lhs.y_,
                        rhs.z_*lhs.x_-rhs.x_*lhs.z_,
                            rhs.x_*lhs.y_-rhs.y_*lhs.x_);    
}

float DotProduct(const Vector4f &rhs, const Vector4f &lhs){
    return rhs.x_*lhs.x_+rhs.y_*lhs.y_+rhs.z_*lhs.z_+rhs.w_*lhs.w_;
}

// Only meaningful for vectors(w == 0)
Vector4f CrossProduct(const Vector4f &rhs, const Vector4f &lhs){
#ifdef ASSERT
    assert(Abs(rhs.w_) < FLOAT_ERROR);
    assert(Abs(lhs.w_) < FLOAT_ERROR);
#endif
    return Vector4f(rhs.y_*lhs.z_-rhs.z_*lhs.y_,
                        rhs.z_*lhs.x_-rhs.x_*lhs.z_,
                            rhs.x_*lhs.y_-rhs.y_*lhs.x_, 0.0f);
}

float CrossProduct(const Vector2f &lhs, const Vector2f &rhs){
    return lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;
}

Vector3f operator*(const Vector3f &vector, const Matrix3x3f &matrix){
    Vector3f result;
    result.x_ = vector.x_ * matrix.e00_ + vector.y_ * matrix.e10_ + vector.z_ * matrix.e20_;
    result.y_ = vector.x_ * matrix.e01_ + vector.y_ * matrix.e11_ + vector.z_ * matrix.e21_;
    result.z_ = vector.x_ * matrix.e02_ + vector.y_ * matrix.e12_ + vector.z_ * matrix.e22_;
    return result;
}

Vector3f operator*(const Matrix3x3f &matrix, const Vector3f &vector){
    Vector3f result;
    result.x_ = matrix.e00_ * vector.x_ + matrix.e01_ * vector.y_ + matrix.e02_ * vector.z_;
    result.y_ = matrix.e10_ * vector.x_ + matrix.e11_ * vector.y_ + matrix.e12_ * vector.z_;
    result.z_ = matrix.e20_ * vector.x_ + matrix.e21_ * vector.y_ + matrix.e22_ * vector.z_;
    return result;
}

Matrix3x3f operator*(const Matrix3x3f &lhs, const Matrix3x3f &rhs){
    Matrix3x3f result;
    result.e00_ = lhs.e00_ * rhs.e00_ + lhs.e01_ * rhs.e10_ + lhs.e02_ * rhs.e20_;
    result.e01_ = lhs.e00_ * rhs.e01_ + lhs.e01_ * rhs.e11_ + lhs.e02_ * rhs.e21_;
    result.e02_ = lhs.e00_ * rhs.e02_ + lhs.e01_ * rhs.e12_ + lhs.e02_ * rhs.e22_;
    result.e10_ = lhs.e10_ * rhs.e00_ + lhs.e11_ * rhs.e10_ + lhs.e12_ * rhs.e20_;
    result.e11_ = lhs.e10_ * rhs.e01_ + lhs.e11_ * rhs.e11_ + lhs.e12_ * rhs.e21_;
    result.e12_ = lhs.e10_ * rhs.e02_ + lhs.e11_ * rhs.e12_ + lhs.e12_ * rhs.e22_;
    result.e20_ = lhs.e20_ * rhs.e00_ + lhs.e21_ * rhs.e10_ + lhs.e22_ * rhs.e20_;
    result.e21_ = lhs.e20_ * rhs.e01_ + lhs.e21_ * rhs.e11_ + lhs.e22_ * rhs.e21_;
    result.e22_ = lhs.e20_ * rhs.e02_ + lhs.e21_ * rhs.e12_ + lhs.e22_ * rhs.e22_;
    return result;
}

Vector4f operator*(const Vector4f &vector, const Matrix4x4f &matrix){
    __m128 vX = _mm_shuffle_ps(vector.v_, vector.v_, 0x00);
    __m128 vY = _mm_shuffle_ps(vector.v_, vector.v_, 0x55);
    __m128 vZ = _mm_shuffle_ps(vector.v_, vector.v_, 0xaa);
    __m128 vW = _mm_shuffle_ps(vector.v_, vector.v_, 0xff);

    __m128 r = _mm_mul_ps(vX, matrix.v_[0]);
    r = _mm_add_ps(r, _mm_mul_ps(vY, matrix.v_[1]));
    r = _mm_add_ps(r, _mm_mul_ps(vZ, matrix.v_[2]));
    r = _mm_add_ps(r, _mm_mul_ps(vW, matrix.v_[3]));
    return Vector4f{r};
}

Vector4f operator*(const Matrix4x4f &matrix, const Vector4f &vector){
    Vector4f result;
    result.x_ = matrix.e00_ * vector.x_ + matrix.e01_ * vector.y_ + matrix.e02_ * vector.z_ + matrix.e03_ * vector.w_;
    result.y_ = matrix.e10_ * vector.x_ + matrix.e11_ * vector.y_ + matrix.e12_ * vector.z_ + matrix.e13_ * vector.w_;
    result.z_ = matrix.e20_ * vector.x_ + matrix.e21_ * vector.y_ + matrix.e22_ * vector.z_ + matrix.e23_ * vector.w_;
    result.w_ = matrix.e30_ * vector.x_ + matrix.e31_ * vector.y_ + matrix.e32_ * vector.z_ + matrix.e33_ * vector.w_;
    return result;
}

Matrix4x4f operator*(const Matrix4x4f &lhs, const Matrix4x4f &rhs){
    Matrix4x4f result;
    result.e00_ = lhs.e00_ * rhs.e00_ + lhs.e01_ * rhs.e10_ + lhs.e02_ * rhs.e20_ + lhs.e03_ * rhs.e30_;
    result.e01_ = lhs.e00_ * rhs.e01_ + lhs.e01_ * rhs.e11_ + lhs.e02_ * rhs.e21_ + lhs.e03_ * rhs.e31_;
    result.e02_ = lhs.e00_ * rhs.e02_ + lhs.e01_ * rhs.e12_ + lhs.e02_ * rhs.e22_ + lhs.e03_ * rhs.e32_;
    result.e03_ = lhs.e00_ * rhs.e03_ + lhs.e01_ * rhs.e13_ + lhs.e02_ * rhs.e23_ + lhs.e03_ * rhs.e33_;

    result.e10_ = lhs.e10_ * rhs.e00_ + lhs.e11_ * rhs.e10_ + lhs.e12_ * rhs.e20_ + lhs.e13_ * rhs.e30_;
    result.e11_ = lhs.e10_ * rhs.e01_ + lhs.e11_ * rhs.e11_ + lhs.e12_ * rhs.e21_ + lhs.e13_ * rhs.e31_;
    result.e12_ = lhs.e10_ * rhs.e02_ + lhs.e11_ * rhs.e12_ + lhs.e12_ * rhs.e22_ + lhs.e13_ * rhs.e32_;
    result.e13_ = lhs.e10_ * rhs.e03_ + lhs.e11_ * rhs.e13_ + lhs.e12_ * rhs.e23_ + lhs.e13_ * rhs.e33_;

    result.e20_ = lhs.e20_ * rhs.e00_ + lhs.e21_ * rhs.e10_ + lhs.e22_ * rhs.e20_ + lhs.e23_ * rhs.e30_;
    result.e21_ = lhs.e20_ * rhs.e01_ + lhs.e21_ * rhs.e11_ + lhs.e22_ * rhs.e21_ + lhs.e23_ * rhs.e31_;
    result.e22_ = lhs.e20_ * rhs.e02_ + lhs.e21_ * rhs.e12_ + lhs.e22_ * rhs.e22_ + lhs.e23_ * rhs.e32_;
    result.e23_ = lhs.e20_ * rhs.e03_ + lhs.e21_ * rhs.e13_ + lhs.e22_ * rhs.e23_ + lhs.e23_ * rhs.e33_;

    result.e30_ = lhs.e30_ * rhs.e00_ + lhs.e31_ * rhs.e10_ + lhs.e32_ * rhs.e20_ + lhs.e33_ * rhs.e30_;
    result.e31_ = lhs.e30_ * rhs.e01_ + lhs.e31_ * rhs.e11_ + lhs.e32_ * rhs.e21_ + lhs.e33_ * rhs.e31_;
    result.e32_ = lhs.e30_ * rhs.e02_ + lhs.e31_ * rhs.e12_ + lhs.e32_ * rhs.e22_ + lhs.e33_ * rhs.e32_;
    result.e33_ = lhs.e30_ * rhs.e03_ + lhs.e31_ * rhs.e13_ + lhs.e32_ * rhs.e23_ + lhs.e33_ * rhs.e33_;
    return result;

    // return Matrix4x4f{MulVecMat_SSE(lhs.v_[0], rhs), MulVecMat_SSE(lhs.v_[1], rhs),
    //         MulVecMat_SSE(lhs.v_[2], rhs), MulVecMat_SSE(lhs.v_[3], rhs)};
}

}
