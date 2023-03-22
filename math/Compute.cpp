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

}
