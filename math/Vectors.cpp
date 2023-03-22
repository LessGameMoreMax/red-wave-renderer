#ifdef ASSERT
#include <assert.h>
#endif

#include <xmmintrin.h>
#include "Vectors.h"
#include "Tools.h"
namespace sablin{

Vector3f::Vector3f(float x, float y, float z):
    x_(x),y_(y),z_(z){}

Vector3f& Vector3f::operator+=(const Vector3f &rhs){ 
#ifdef OPTIMIZE
#else
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
#endif
    return *this;
}

Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs){
    Vector3f sum = lhs;
    sum += rhs;
    return sum;
}

Vector3f& Vector3f::operator+=(const float f_number){
#ifdef OPTIMIZE
#else
    x_ += f_number;
    y_ += f_number;
    z_ += f_number;
#endif
    return *this;
}

Vector3f operator+(const Vector3f &lhs, const float f_number){
    Vector3f sum = lhs;
    sum += f_number;
    return sum;
}

Vector3f& Vector3f::operator-=(const Vector3f &rhs){ 
#ifdef OPTIMIZE
#else
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
#endif
    return *this;
}

Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs){
    Vector3f sum = lhs;
    sum -= rhs;
    return sum;
}

Vector3f& Vector3f::operator-=(const float f_number){
#ifdef OPTIMIZE
#else
    x_ -= f_number;
    y_ -= f_number;
    z_ -= f_number;
#endif
    return *this;
}

Vector3f operator-(const Vector3f &lhs, const float f_number){
    Vector3f sum = lhs;
    sum -= f_number;
    return sum;
}

bool operator==(const Vector3f &lhs, const Vector3f &rhs){
    return Abs(lhs.x_ - rhs.x_) < FLOAT_ERROR &&
                Abs(lhs.y_ - rhs.y_) < FLOAT_ERROR &&
                    Abs(lhs.z_ - rhs.z_) < FLOAT_ERROR;
}

bool operator!=(const Vector3f &lhs, const Vector3f &rhs){
    return !(lhs == rhs);
}

float Vector3f::Norm() const{
    return Sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

void Vector3f::Normalized(){
    float rnorm = Rsqrt(x_ * x_ + y_ * y_ + z_ * z_);
    x_ *= rnorm;
    y_ *= rnorm;
    z_ *= rnorm;
}

Vector4f::Vector4f(float x, float y, float z, float w):
    x_(x),y_(y),z_(z),w_(w){}

}
