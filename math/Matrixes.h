#ifndef MATRIXES_H
#define MATRIXES_H
namespace sablin{

class Matrix3x3f{
public:
    union{
        struct{
            float e00_,e01_,e02_;
            float e10_,e11_,e12_;
            float e20_,e21_,e22_;
        };
        float m_[3][3];
        float s_[9];
    };

    Matrix3x3f():e00_(0.0f),e01_(0.0f),e02_(0.0f),
                    e10_(0.0f),e11_(0.0f),e12_(0.0f),
                        e20_(0.0f),e21_(0.0f),e22_(0.0f){}

    Matrix3x3f(float e00, float e01, float e02,
                    float e10, float e11, float e12,
                        float e20, float e21, float e22);

    Matrix3x3f(const Matrix3x3f&) = default;
    Matrix3x3f(Matrix3x3f&&) = default;
    Matrix3x3f& operator=(const Matrix3x3f&) = default;
    Matrix3x3f& operator=(Matrix3x3f&&) = default;
    ~Matrix3x3f() = default;

    Matrix3x3f& operator+=(const Matrix3x3f&);
    Matrix3x3f& operator+=(const float);
    Matrix3x3f& operator-=(const Matrix3x3f&);
    Matrix3x3f& operator-=(const float);
    Matrix3x3f& operator*=(const float);
    Matrix3x3f& operator/=(const float);

    Matrix3x3f Transpose() const;
    void       Transposed();
    Matrix3x3f Inverse() const;
    void       Inversed();
    float      Det() const;
}__attribute__((aligned(16)));

Matrix3x3f operator+(const Matrix3x3f&, const Matrix3x3f&);
Matrix3x3f operator-(const Matrix3x3f&, const Matrix3x3f&);
Matrix3x3f operator+(const Matrix3x3f&, const float);
Matrix3x3f operator-(const Matrix3x3f&, const float);
Matrix3x3f operator*(const Matrix3x3f&, const float);
Matrix3x3f operator/(const Matrix3x3f&, const float);
bool       operator==(const Matrix3x3f&, const Matrix3x3f&);
bool       operator!=(const Matrix3x3f&, const Matrix3x3f&);

class Matrix4x4f{
public:
    union{
        struct{
            float e00_,e01_,e02_,e03_;
            float e10_,e11_,e12_,e13_;
            float e20_,e21_,e22_,e23_;
            float e30_,e31_,e32_,e33_;
        };
        float m_[4][4];
        float s_[16];
    };

    Matrix4x4f():e00_(0.0f),e01_(0.0f),e02_(0.0f),e03_(0.0f),
                    e10_(0.0f),e11_(0.0f),e12_(0.0f),e13_(0.0f),
                        e20_(0.0f),e21_(0.0f),e22_(0.0f),e23_(0.0f),
                            e30_(0.0f),e31_(0.0f),e32_(0.0f),e33_(0.0f){}

    Matrix4x4f(float e00, float e01, float e02, float e03,
                    float e10, float e11, float e12, float e13,
                        float e20, float e21, float e22, float e23,
                            float e30, float e31, float e32, float e33);

    Matrix4x4f(const Matrix4x4f&) = default;
    Matrix4x4f(Matrix4x4f&&) = default;
    Matrix4x4f& operator=(const Matrix4x4f&) = default;
    Matrix4x4f& operator=(Matrix4x4f&&) = default;
    ~Matrix4x4f() = default;

    Matrix4x4f& operator+=(const Matrix4x4f&);
    Matrix4x4f& operator+=(const float);
    Matrix4x4f& operator-=(const Matrix4x4f&);
    Matrix4x4f& operator-=(const float);
    Matrix4x4f& operator*=(const float);
    Matrix4x4f& operator/=(const float);

    Matrix4x4f Transpose() const;
    void       Transposed();
    Matrix4x4f Inverse() const;
    void       Inversed();
    float      Det() const;
}__attribute__((aligned(16)));

Matrix4x4f operator+(const Matrix4x4f&, const Matrix4x4f&);
Matrix4x4f operator-(const Matrix4x4f&, const Matrix4x4f&);
Matrix4x4f operator+(const Matrix4x4f&, const float);
Matrix4x4f operator-(const Matrix4x4f&, const float);
Matrix4x4f operator*(const Matrix4x4f&, const float);
Matrix4x4f operator/(const Matrix4x4f&, const float);
bool       operator==(const Matrix4x4f&, const Matrix4x4f&);
bool       operator!=(const Matrix4x4f&, const Matrix4x4f&);

}
#endif
