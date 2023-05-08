#ifndef COMPUTE_H
#define COMPUTE_H
#include "Vectors.h"
#include "Matrixes.h"
namespace sablin{

float DotProduct(const Vector3f&, const Vector3f&);
Vector3f CrossProduct(const Vector3f&, const Vector3f&);

float DotProduct(const Vector4f&, const Vector4f&);
Vector4f CrossProduct(const Vector4f&, const Vector4f&);

float CrossProduct(const Vector2f&, const Vector2f&);

Vector3f operator*(const Vector3f&, const Matrix3x3f&);
Vector3f operator*(const Matrix3x3f&, const Vector3f&);

Matrix3x3f operator*(const Matrix3x3f&, const Matrix3x3f&);

Vector4f operator*(const Vector4f&, const Matrix4x4f&);
Vector4f operator*(const Matrix4x4f&, const Vector4f&);

Matrix4x4f operator*(const Matrix4x4f&, const Matrix4x4f&);
}
#endif
