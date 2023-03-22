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

}
