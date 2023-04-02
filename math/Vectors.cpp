#ifdef ASSERT
#include <assert.h>
#endif

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

Vector4f& Vector4f::operator+=(const Vector4f &rhs){
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    w_ += rhs.w_;
    return *this;
}

Vector4f operator+(const Vector4f &lhs, const Vector4f &rhs){
    Vector4f sum = lhs;
    sum += rhs;
    return sum;
}

Vector4f& Vector4f::operator+=(const float f_number){
    x_ += f_number;
    y_ += f_number;
    z_ += f_number;
    w_ += f_number;
    return *this;
}

Vector4f operator+(const Vector4f &rhs, const float f_number){
    Vector4f sum = rhs;
    sum += f_number;
    return sum;
}

Vector4f& Vector4f::operator-=(const Vector4f &rhs){
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    w_ -= rhs.w_;
    return *this;
}

Vector4f operator-(const Vector4f &lhs, const Vector4f &rhs){
    Vector4f sum = lhs;
    sum -= rhs;
    return sum;
}

Vector4f& Vector4f::operator-=(const float f_number){
    x_ -= f_number;
    y_ -= f_number;
    z_ -= f_number;
    w_ -= f_number;
    return *this;
}

Vector4f operator-(const Vector4f &rhs, const float f_number){
    Vector4f sum = rhs;
    sum -= f_number;
    return sum;
}

bool operator==(const Vector4f &rhs, const Vector4f &lhs){
    return Abs(rhs.x_ - lhs.x_) < FLOAT_ERROR &&
                Abs(rhs.y_ - lhs.y_) < FLOAT_ERROR &&
                    Abs(rhs.z_ - lhs.z_) < FLOAT_ERROR &&
                        Abs(rhs.w_ - lhs.w_) < FLOAT_ERROR;
}

bool operator!=(const Vector4f &rhs, const Vector4f &lhs){
    return !(rhs == lhs);
}

float Vector4f::Norm() const{
    return Sqrt(x_*x_+ y_*y_+ z_*z_+ w_*w_);
}

void Vector4f::Normalized(){
   float rnorm = Rsqrt(x_*x_+y_*y_+z_*z_+w_*w_);
   x_ *= rnorm;
   y_ *= rnorm;
   z_ *= rnorm;
   w_ *= rnorm;
}

Vector3i::Vector3i(int32_t x, int32_t y, int32_t z):
    x_(x),y_(y),z_(z){}

Vector3i& Vector3i::operator+=(const Vector3i &rhs){ 
#ifdef OPTIMIZE
#else
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
#endif
    return *this;
}

Vector3i operator+(const Vector3i &lhs, const Vector3i &rhs){
    Vector3i sum = lhs;
    sum += rhs;
    return sum;
}

Vector3i& Vector3i::operator+=(const int32_t i_number){
#ifdef OPTIMIZE
#else
    x_ += i_number;
    y_ += i_number;
    z_ += i_number;
#endif
    return *this;
}

Vector3i operator+(const Vector3i &lhs, const int32_t i_number){
    Vector3i sum = lhs;
    sum += i_number;
    return sum;
}

Vector3i& Vector3i::operator-=(const Vector3i &rhs){ 
#ifdef OPTIMIZE
#else
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
#endif
    return *this;
}

Vector3i operator-(const Vector3i &lhs, const Vector3i &rhs){
    Vector3i sum = lhs;
    sum -= rhs;
    return sum;
}

Vector3i& Vector3i::operator-=(const int32_t i_number){
#ifdef OPTIMIZE
#else
    x_ -= i_number;
    y_ -= i_number;
    z_ -= i_number;
#endif
    return *this;
}

Vector3i operator-(const Vector3i &lhs, const int32_t i_number){
    Vector3i sum = lhs;
    sum -= i_number;
    return sum;
}

bool operator==(const Vector3i &lhs, const Vector3i &rhs){
    return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_ && lhs.z_ == rhs.z_;
}

bool operator!=(const Vector3i &lhs, const Vector3i &rhs){
    return !(lhs == rhs);
}

float Vector3i::Norm() const{
    return Sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

Vector4i::Vector4i(int32_t x, int32_t y, int32_t z, int32_t w):
    x_(x),y_(y),z_(z),w_(w){}

Vector4i& Vector4i::operator+=(const Vector4i &rhs){
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    w_ += rhs.w_;
    return *this;
}

Vector4i operator+(const Vector4i &lhs, const Vector4i &rhs){
    Vector4i sum = lhs;
    sum += rhs;
    return sum;
}

Vector4i& Vector4i::operator+=(const int32_t i_number){
    x_ += i_number;
    y_ += i_number;
    z_ += i_number;
    w_ += i_number;
    return *this;
}

Vector4i operator+(const Vector4i &rhs, const int32_t i_number){
    Vector4i sum = rhs;
    sum += i_number;
    return sum;
}

Vector4i& Vector4i::operator-=(const Vector4i &rhs){
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    w_ -= rhs.w_;
    return *this;
}

Vector4i operator-(const Vector4i &lhs, const Vector4i &rhs){
    Vector4i sum = lhs;
    sum -= rhs;
    return sum;
}

Vector4i& Vector4i::operator-=(const int32_t i_number){
    x_ -= i_number;
    y_ -= i_number;
    z_ -= i_number;
    w_ -= i_number;
    return *this;
}

Vector4i operator-(const Vector4i &rhs, const int32_t i_number){
    Vector4i sum = rhs;
    sum -= i_number;
    return sum;
}

bool operator==(const Vector4i &rhs, const Vector4i &lhs){
    return rhs.x_ == lhs.x_ && rhs.y_ == lhs.y_ &&
                rhs.z_ == lhs.z_ && rhs.w_ == lhs.w_;
}

bool operator!=(const Vector4i &rhs, const Vector4i &lhs){
    return !(rhs == lhs);
}

float Vector4i::Norm() const{
    return Sqrt(x_*x_+ y_*y_+ z_*z_+ w_*w_);
}

}
