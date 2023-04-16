#include "Matrixes.h"
#include "Tools.h"
namespace sablin{

Matrix3x3f::Matrix3x3f(float e00, float e01, float e02,
                float e10, float e11, float e12,
                    float e20, float e21, float e22):
            e00_(e00),e01_(e01),e02_(e02),
                e10_(e10),e11_(e11),e12_(e12),
                    e20_(e20),e21_(e21),e22_(e22){}

Matrix3x3f& Matrix3x3f::operator+=(const Matrix3x3f &lhs){
    for(int8_t i = 0;i != 9; ++i)
        s_[i] += lhs.s_[i];
    return *this;
}

Matrix3x3f operator+(const Matrix3x3f &lhs, const Matrix3x3f &rhs){
    Matrix3x3f sum = lhs;
    sum += rhs;
    return sum;
}

Matrix3x3f& Matrix3x3f::operator+=(const float f_number){
    for(int8_t i = 0;i != 9; ++i)
        s_[i] += f_number;
    return *this;
}

Matrix3x3f operator+(const Matrix3x3f &lhs, const float f_number){
    Matrix3x3f sum = lhs;
    sum += f_number;
    return sum;
}

Matrix3x3f& Matrix3x3f::operator-=(const Matrix3x3f &rhs){
    for(int8_t i = 0;i != 9; ++i)
        s_[i] -= rhs.s_[i];
    return *this;
}

Matrix3x3f operator-(const Matrix3x3f &lhs, const Matrix3x3f &rhs){
    Matrix3x3f sum = lhs;
    sum -= rhs;
    return sum;
}

Matrix3x3f& Matrix3x3f::operator-=(const float f_number){
    for(int8_t i = 0;i != 9; ++i)
        s_[i] -= f_number;
    return *this;
}

Matrix3x3f operator-(const Matrix3x3f &lhs, const float f_number){
    Matrix3x3f sum = lhs;
    sum -= f_number;
    return sum;
}

Matrix3x3f& Matrix3x3f::operator*=(const float f_number){
    for(int8_t i = 0; i != 9; ++i)
        s_[i] *= f_number;
    return *this;
}

Matrix3x3f operator*(const Matrix3x3f &lhs, const float f_number){
    Matrix3x3f multi = lhs;
    multi *= f_number;
    return multi;
}

Matrix3x3f& Matrix3x3f::operator/=(const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    for(int8_t i = 0;i != 9; ++i)
        s_[i] /= f_number;
    return *this;
}

Matrix3x3f operator/(const Matrix3x3f &lhs, const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    Matrix3x3f div = lhs;
    div /= f_number;
    return div;
}

bool operator==(const Matrix3x3f &lhs, const Matrix3x3f &rhs){
    for(int8_t i = 0;i != 9; ++i)
        if(Abs(lhs.s_[i] - rhs.s_[i]) > FLOAT_ERROR)
            return false;
    return true;
}

bool operator!=(const Matrix3x3f &lhs, const Matrix3x3f &rhs){
    return !(lhs == rhs);
}

Matrix3x3f Matrix3x3f::Transpose() const{
    Matrix3x3f result(*this);
    Swap(result.m_[0][1], result.m_[1][0]);
    Swap(result.m_[0][2], result.m_[2][0]);
    Swap(result.m_[1][2], result.m_[2][1]);
    return result;
}

void Matrix3x3f::Transposed(){
    Swap(m_[0][1], m_[1][0]);
    Swap(m_[0][2], m_[2][0]);
    Swap(m_[1][2], m_[2][1]);
}

float Matrix3x3f::Det() const{
    return s_[0]*s_[4]*s_[8]+s_[1]*s_[5]*s_[6]+s_[3]*s_[7]*s_[2]
                -s_[2]*s_[4]*s_[6]-s_[1]*s_[3]*s_[8]-s_[5]*s_[7]*s_[0];
}

Matrix3x3f Matrix3x3f::Inverse() const{
    Matrix3x3f A(*this);
    Vector3i pi = LUPDecomposition3x3f(A);
    Matrix3x3f L{
        1.0f,   0.0f,   0.0f,
        A.e10_, 1.0f,   0.0f,
        A.e20_, A.e21_, 1.0f
    };
    Matrix3x3f U{
        A.e00_, A.e01_, A.e02_,
        0.0f,   A.e11_, A.e12_,
        0.0f,   0.0f,   A.e22_
    };
    Vector3f b0{1.0f, 0.0f, 0.0f};
    Vector3f b1{0.0f, 1.0f, 0.0f};
    Vector3f b2{0.0f, 0.0f, 1.0f};
    b0 = LUPSolve3f(L, U, pi, b0);
    b1 = LUPSolve3f(L, U, pi, b1);
    b2 = LUPSolve3f(L, U, pi, b2);
    return Matrix3x3f{b0.x_, b1.x_, b2.x_,
                      b0.y_, b1.y_, b2.y_,
                      b0.z_, b1.z_, b2.z_};
}

void Matrix3x3f::Inversed(){
    Matrix3x3f A(*this);
    Vector3i pi = LUPDecomposition3x3f(A);
    Matrix3x3f L{
        1.0f,   0.0f,   0.0f,
        A.e10_, 1.0f,   0.0f,
        A.e20_, A.e21_, 1.0f
    };
    Matrix3x3f U{
        A.e00_, A.e01_, A.e02_,
        0.0f,   A.e11_, A.e12_,
        0.0f,   0.0f,   A.e22_
    };
    Vector3f b0{1.0f, 0.0f, 0.0f};
    Vector3f b1{0.0f, 1.0f, 0.0f};
    Vector3f b2{0.0f, 0.0f, 1.0f};
    b0 = LUPSolve3f(L, U, pi, b0);
    b1 = LUPSolve3f(L, U, pi, b1);
    b2 = LUPSolve3f(L, U, pi, b2);
    e00_ = b0.x_; e01_ = b1.x_; e02_ = b2.x_; 
    e10_ = b0.y_; e11_ = b1.y_; e12_ = b2.y_; 
    e20_ = b0.z_; e21_ = b1.z_; e22_ = b2.z_; 
}

Matrix4x4f::Matrix4x4f(float e00, float e01, float e02, float e03,
                float e10, float e11, float e12, float e13,
                    float e20, float e21, float e22, float e23,
                        float e30, float e31, float e32, float e33):
            e00_(e00),e01_(e01),e02_(e02),e03_(e03),
                e10_(e10),e11_(e11),e12_(e12),e13_(e13),
                    e20_(e20),e21_(e21),e22_(e22),e23_(e23),
                        e30_(e30),e31_(e31),e32_(e32),e33_(e33){}

Matrix4x4f::Matrix4x4f(__m128 v0, __m128 v1, __m128 v2, __m128 v3){
    v_[0] = v0;
    v_[1] = v1;
    v_[2] = v2;
    v_[3] = v3;
}

Matrix4x4f Matrix4x4f::Transpose() const{
    __m128 tmp0 = _mm_shuffle_ps(v_[0], v_[1], 0x44);
    __m128 tmp2 = _mm_shuffle_ps(v_[0], v_[1], 0xee);
    __m128 tmp1 = _mm_shuffle_ps(v_[2], v_[3], 0x44);
    __m128 tmp3 = _mm_shuffle_ps(v_[2], v_[3], 0xee);

    Matrix4x4f result(*this);
    result.v_[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);
    result.v_[1] = _mm_shuffle_ps(tmp0, tmp1, 0xdd);
    result.v_[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);
    result.v_[3] = _mm_shuffle_ps(tmp2, tmp3, 0xdd);
    return result;
}

void Matrix4x4f::Transposed(){
    __m128 tmp0 = _mm_shuffle_ps(v_[0], v_[1], 0x44);
    __m128 tmp2 = _mm_shuffle_ps(v_[0], v_[1], 0xee);
    __m128 tmp1 = _mm_shuffle_ps(v_[2], v_[3], 0x44);
    __m128 tmp3 = _mm_shuffle_ps(v_[2], v_[3], 0xee);

    v_[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);
    v_[1] = _mm_shuffle_ps(tmp0, tmp1, 0xdd);
    v_[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);
    v_[3] = _mm_shuffle_ps(tmp2, tmp3, 0xdd);
}

float Matrix4x4f::Det() const{
    Matrix4x4f A(*this);
    LUPDecomposition4x4f(A);
    return -(A.e00_ * A.e11_ * A.e22_ * A.e33_);
}

Matrix4x4f Matrix4x4f::Inverse() const{
    Matrix4x4f A(*this);
    Vector4i pi = LUPDecomposition4x4f(A);
    Matrix4x4f L{
        1.0f,   0.0f,   0.0f,   0.0f,
        A.e10_, 1.0f,   0.0f,   0.0f,
        A.e20_, A.e21_, 1.0f,   0.0f,
        A.e30_, A.e31_, A.e32_, 1.0f
    };
    Matrix4x4f U{
        A.e00_, A.e01_, A.e02_, A.e03_,
        0.0f,   A.e11_, A.e12_, A.e13_,
        0.0f,   0.0f,   A.e22_, A.e23_,
        0.0f,   0.0f,   0.0f,   A.e33_
    };
    Vector4f b0{1.0f, 0.0f, 0.0f, 0.0f};
    Vector4f b1{0.0f, 1.0f, 0.0f, 0.0f};
    Vector4f b2{0.0f, 0.0f, 1.0f, 0.0f};
    Vector4f b3{0.0f, 0.0f, 0.0f, 1.0f};
    b0 = LUPSolve4f(L, U, pi, b0);
    b1 = LUPSolve4f(L, U, pi, b1);
    b2 = LUPSolve4f(L, U, pi, b2);
    b3 = LUPSolve4f(L, U, pi, b3);
    return Matrix4x4f{b0.x_, b1.x_, b2.x_, b3.x_,
                      b0.y_, b1.y_, b2.y_, b3.y_,
                      b0.z_, b1.z_, b2.z_, b3.z_,
                      b0.w_, b1.w_, b2.w_, b3.w_};
}

void Matrix4x4f::Inversed(){
    Matrix4x4f A(*this);
    Vector4i pi = LUPDecomposition4x4f(A);
    Matrix4x4f L{
        1.0f,   0.0f,   0.0f,   0.0f,
        A.e10_, 1.0f,   0.0f,   0.0f,
        A.e20_, A.e21_, 1.0f,   0.0f,
        A.e30_, A.e31_, A.e32_, 1.0f
    };
    Matrix4x4f U{
        A.e00_, A.e01_, A.e02_, A.e03_,
        0.0f,   A.e11_, A.e12_, A.e13_,
        0.0f,   0.0f,   A.e22_, A.e23_,
        0.0f,   0.0f,   0.0f,   A.e33_
    };
    Vector4f b0{1.0f, 0.0f, 0.0f, 0.0f};
    Vector4f b1{0.0f, 1.0f, 0.0f, 0.0f};
    Vector4f b2{0.0f, 0.0f, 1.0f, 0.0f};
    Vector4f b3{0.0f, 0.0f, 0.0f, 1.0f};
    b0 = LUPSolve4f(L, U, pi, b0);
    b1 = LUPSolve4f(L, U, pi, b1);
    b2 = LUPSolve4f(L, U, pi, b2);
    b3 = LUPSolve4f(L, U, pi, b3);
    e00_ = b0.x_; e01_ = b1.x_; e02_ = b2.x_; e03_ = b3.x_;
    e10_ = b0.y_; e11_ = b1.y_; e12_ = b2.y_; e13_ = b3.y_;
    e20_ = b0.z_; e21_ = b1.z_; e22_ = b2.z_; e23_ = b3.z_;
    e30_ = b0.w_; e31_ = b1.w_; e32_ = b2.w_; e33_ = b3.w_;
}

Matrix4x4f& Matrix4x4f::operator+=(const Matrix4x4f &lhs){
    for(int8_t i = 0;i != 4; ++i)
        v_[i] = _mm_add_ps(v_[i], lhs.v_[i]);
    return *this;
}

Matrix4x4f operator+(const Matrix4x4f &lhs, const Matrix4x4f &rhs){
    Matrix4x4f sum = lhs;
    sum += rhs;
    return sum;
}

Matrix4x4f& Matrix4x4f::operator+=(const float f_number){
    __m128 m_b = _mm_set1_ps(f_number);
    for(int8_t i = 0;i != 4; ++i)
        v_[i] = _mm_add_ps(v_[i], m_b);
    return *this;
}

Matrix4x4f operator+(const Matrix4x4f &lhs, const float f_number){
    Matrix4x4f sum = lhs;
    sum += f_number;
    return sum;
}

Matrix4x4f& Matrix4x4f::operator-=(const Matrix4x4f &rhs){
    for(int8_t i = 0;i != 4; ++i)
        v_[i] = _mm_sub_ps(v_[i], rhs.v_[i]);
    return *this;
}

Matrix4x4f operator-(const Matrix4x4f &lhs, const Matrix4x4f &rhs){
    Matrix4x4f sum = lhs;
    sum -= rhs;
    return sum;
}

Matrix4x4f& Matrix4x4f::operator-=(const float f_number){
    __m128 m_b = _mm_set1_ps(f_number);
    for(int8_t i = 0;i != 4; ++i)
        v_[i] = _mm_sub_ps(v_[i], m_b);
    return *this;
}

Matrix4x4f operator-(const Matrix4x4f &lhs, const float f_number){
    Matrix4x4f sum = lhs;
    sum -= f_number;
    return sum;
}

Matrix4x4f& Matrix4x4f::operator*=(const float f_number){
    __m128 m_b = _mm_set1_ps(f_number);
    for(int8_t i = 0;i != 4; ++i)
        v_[i] = _mm_mul_ps(v_[i], m_b);
    return *this;
}

Matrix4x4f operator*(const Matrix4x4f &lhs, const float f_number){
    Matrix4x4f multi = lhs;
    multi *= f_number;
    return multi;
}

Matrix4x4f& Matrix4x4f::operator/=(const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    __m128 m_b = _mm_set1_ps(f_number);
    for(int8_t i = 0;i != 4; ++i)
        v_[i] = _mm_div_ps(v_[i], m_b);
    return *this;
}

Matrix4x4f operator/(const Matrix4x4f &lhs, const float f_number){
#ifdef ASSERT
    assert(Abs(f_number) > FLOAT_ERROR);
#endif
    Matrix4x4f div = lhs;
    div /= f_number;
    return div;
}

bool operator==(const Matrix4x4f &lhs, const Matrix4x4f &rhs){
    for(int8_t i = 0;i != 16; ++i)
        if(Abs(lhs.s_[i] - rhs.s_[i]) > FLOAT_ERROR)
            return false;
    return true;
}

bool operator!=(const Matrix4x4f &lhs, const Matrix4x4f &rhs){
    return !(lhs == rhs);
}

}
