#ifndef CAMERA_H
#define CAMERA_H
#include "../math/Vectors.h"
#include "../math/Matrixes.h"
namespace sablin{
class Camera{ 
private:
    Vector4f world_position_;
    Vector4f target_position_;
    Vector4f up_direction_;
    Matrix4x4f view_matrix_;
private:
    void FreshViewMatrix();
public: 
    Camera(const Vector4f&, const Vector4f&,
            const Vector4f&);
    Camera(const Camera&) = default;
    Camera& operator=(const Camera&) = default;
    ~Camera() = default;
    Matrix4x4f GetViewMatrix() const;
};
}
#endif
