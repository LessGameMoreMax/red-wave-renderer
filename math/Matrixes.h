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
};

}
#endif
