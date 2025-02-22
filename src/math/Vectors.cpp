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

Vector3f& Vector3f::operator*=(const float f_number){
    x_ *= f_number;
    y_ *= f_number;
    z_ *= f_number;
    return *this;
}

Vector3f operator*(const Vector3f &lhs, const float f_number){
    Vector3f multi = lhs;
    multi *= f_number;
    return multi;
}

Vector3f operator*(const Vector3f &lhs, const Vector3f &rhs){
    return Vector3f{lhs.x_ * rhs.x_, lhs.y_ * rhs.y_, lhs.z_ * rhs.z_};
}

Vector3f& Vector3f::operator/=(const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    x_ /= f_number;
    y_ /= f_number;
    z_ /= f_number;
    return *this;
}

Vector3f operator/(const Vector3f &lhs, const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    Vector3f div = lhs;
    div /= f_number;
    return div;
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

Vector3f Vector3f::Normalized(){
    float rnorm = Rsqrt(x_ * x_ + y_ * y_ + z_ * z_);
    x_ *= rnorm;
    y_ *= rnorm;
    z_ *= rnorm;
    return *this;
}

Vector4f::Vector4f(float x, float y, float z, float w):
    x_(x),y_(y),z_(z),w_(w){}

Vector4f::Vector4f(__m128 v): v_(v){}

Vector4f::Vector4f(const Vector3f &xyz, float w):
    x_(xyz.x_), y_(xyz.y_), z_(xyz.z_), w_(w){}

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

Vector4f operator-(const float f_number, const Vector4f &lhs){
    Vector4f sum = lhs;
    sum.x_ = f_number - lhs.x_;
    sum.y_ = f_number - lhs.y_;
    sum.z_ = f_number - lhs.z_;
    sum.w_ = f_number - lhs.w_;
    return sum;
}

Vector4f operator-(const Vector4f &lhs){
    Vector4f sum = lhs;
    sum.x_ = -lhs.x_;
    sum.y_ = -lhs.y_;
    sum.z_ = -lhs.z_;
    sum.w_ = -lhs.w_;
    return sum;
}

Vector4f& Vector4f::operator*=(const float f_number){
    x_ *= f_number;
    y_ *= f_number;
    z_ *= f_number;
    w_ *= f_number;
    return *this;
}

Vector4f operator*(const Vector4f &lhs, const float f_number){
    Vector4f multi = lhs;
    multi *= f_number;
    return multi;
}

Vector4f operator*(const Vector4f &lhs, const Vector4f &rhs){
    return Vector4f(_mm_mul_ps(lhs.v_, rhs.v_));
}

Vector4f& Vector4f::operator/=(const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    x_ /= f_number;
    y_ /= f_number;
    z_ /= f_number;
    w_ /= f_number;
    return *this;
}

Vector4f operator/(const Vector4f &lhs, const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    Vector4f div = lhs;
    div /= f_number;
    return div;
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

Vector4f Vector4f::Normalized(){
   float rnorm = Rsqrt(x_*x_+y_*y_+z_*z_+w_*w_);
   x_ *= rnorm;
   y_ *= rnorm;
   z_ *= rnorm;
   w_ *= rnorm;
   return *this;
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

Vector2f::Vector2f(float x, float y):
    x_(x),y_(y){}

Vector2f& Vector2f::operator+=(const Vector2f &rhs){ 
#ifdef OPTIMIZE
#else
    x_ += rhs.x_;
    y_ += rhs.y_;
#endif
    return *this;
}

Vector2f operator+(const Vector2f &lhs, const Vector2f &rhs){
    Vector2f sum = lhs;
    sum += rhs;
    return sum;
}

Vector2f& Vector2f::operator+=(const float f_number){
#ifdef OPTIMIZE
#else
    x_ += f_number;
    y_ += f_number;
#endif
    return *this;
}

Vector2f operator+(const Vector2f &lhs, const float f_number){
    Vector2f sum = lhs;
    sum += f_number;
    return sum;
}

Vector2f& Vector2f::operator-=(const Vector2f &rhs){ 
#ifdef OPTIMIZE
#else
    x_ -= rhs.x_;
    y_ -= rhs.y_;
#endif
    return *this;
}

Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs){
    Vector2f sum = lhs;
    sum -= rhs;
    return sum;
}

Vector2f& Vector2f::operator-=(const float f_number){
#ifdef OPTIMIZE
#else
    x_ -= f_number;
    y_ -= f_number;
#endif
    return *this;
}

Vector2f operator-(const Vector2f &lhs, const float f_number){
    Vector2f sum = lhs;
    sum -= f_number;
    return sum;
}

Vector2f& Vector2f::operator*=(const float f_number){
    x_ *= f_number;
    y_ *= f_number;
    return *this;
}

Vector2f operator*(const Vector2f &lhs, const float f_number){
    Vector2f multi = lhs;
    multi *= f_number;
    return multi;
}

Vector2f& Vector2f::operator/=(const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    x_ /= f_number;
    y_ /= f_number;
    return *this;
}

Vector2f operator/(const Vector2f &lhs, const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    Vector2f div = lhs;
    div /= f_number;
    return div;
}

bool operator==(const Vector2f &lhs, const Vector2f &rhs){
    return Abs(lhs.x_ - rhs.x_) < FLOAT_ERROR &&
                Abs(lhs.y_ - rhs.y_) < FLOAT_ERROR;
}

bool operator!=(const Vector2f &lhs, const Vector2f &rhs){
    return !(lhs == rhs);
}

Vector2i::Vector2i(int32_t x, int32_t y):
    x_(x),y_(y){}

Vector2i& Vector2i::operator+=(const Vector2i &rhs){ 
#ifdef OPTIMIZE
#else
    x_ += rhs.x_;
    y_ += rhs.y_;
#endif
    return *this;
}

Vector2i operator+(const Vector2i &lhs, const Vector2i &rhs){
    Vector2i sum = lhs;
    sum += rhs;
    return sum;
}

Vector2i& Vector2i::operator+=(const int32_t i_number){
#ifdef OPTIMIZE
#else
    x_ += i_number;
    y_ += i_number;
#endif
    return *this;
}

Vector2i operator+(const Vector2i &lhs, const int32_t i_number){
    Vector2i sum = lhs;
    sum += i_number;
    return sum;
}

Vector2i& Vector2i::operator-=(const Vector2i &rhs){ 
#ifdef OPTIMIZE
#else
    x_ -= rhs.x_;
    y_ -= rhs.y_;
#endif
    return *this;
}

Vector2i operator-(const Vector2i &lhs, const Vector2i &rhs){
    Vector2i sum = lhs;
    sum -= rhs;
    return sum;
}

Vector2i& Vector2i::operator-=(const int32_t i_number){
#ifdef OPTIMIZE
#else
    x_ -= i_number;
    y_ -= i_number;
#endif
    return *this;
}

Vector2i operator-(const Vector2i &lhs, const int32_t i_number){
    Vector2i sum = lhs;
    sum -= i_number;
    return sum;
}

Vector2i& Vector2i::operator*=(const int32_t i_number){
    x_ *= i_number;
    y_ *= i_number;
    return *this;
}

Vector2i operator*(const Vector2i &lhs, const int32_t i_number){
    Vector2i multi = lhs;
    multi *= i_number;
    return multi;
}

Vector2i& Vector2i::operator/=(const int32_t i_number){
#ifdef ASSERT
    assert(i_number != 0);
#endif
    x_ /= i_number;
    y_ /= i_number;
    return *this;
}

Vector2i operator/(const Vector2i &lhs, const int32_t i_number){
#ifdef ASSERT
    assert(i_number != 0);
#endif
    Vector2i div = lhs;
    div /= i_number;
    return div;
}

bool operator==(const Vector2i &lhs, const Vector2i &rhs){
    return lhs.x_ == rhs.x_ &&
                lhs.y_ == rhs.y_;
}

bool operator!=(const Vector2i &lhs, const Vector2i &rhs){
    return !(lhs == rhs);
}
}
