#ifndef COMPUTE_H
#define COMPUTE_H
#include "Vectors.h"
#include "Matrixes.h"
namespace sablin{

float DotProduct(const Vector3f&, const Vector3f&);
Vector3f CrossProduct(const Vector3f&, const Vector3f&);

float DotProduct(const Vector4f&, const Vector4f&);
Vector4f CrossProduct(const Vector4f&, const Vector4f&);

}
#endif
