#include "Matrixes.h"
#include "Tools.h"
namespace sablin{

Matrix3x3f::Matrix3x3f(float e00, float e01, float e02,
                float e10, float e11, float e12,
                    float e20, float e21, float e22):
            e00_(e00),e01_(e01),e02_(e02),
                e10_(e10),e11_(e11),e12_(e12),
                    e20_(e20),e21_(e21),e22_(e22){}

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

}
