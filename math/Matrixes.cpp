#include "Matrixes.h"
namespace sablin{

Matrix3x3f::Matrix3x3f(float e00, float e01, float e02,
                float e10, float e11, float e12,
                    float e20, float e21, float e22):
            e00_(e00),e01_(e01),e02_(e02),
                e10_(e10),e11_(e11),e12_(e12),
                    e20_(e20),e21_(e21),e22_(e22){}

}
