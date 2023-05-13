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

    float near_plane_;
    float far_plane_;
    float vertical_fov_radian_;
    float aspect_ratio_;
    Matrix4x4f project_matrix_;
private:
    void FreshViewMatrix();
    void FreshProjectMatrix();
public: 
    Camera(const Vector4f& world_position, 
           const Vector4f& target_position,
           const Vector4f& up_direction,
           const float near_plane, 
           const float far_plane,
           const float vertical_fov_angle,
           const float aspect_ratio);
    Camera(const Camera&) = default;
    Camera& operator=(const Camera&) = default;
    ~Camera() = default;
    Matrix4x4f GetViewMatrix() const;
    Matrix4x4f GetProjectMatrix() const;

    float GetNearPlane() const;
    float GetFarPlane() const;
    Vector4f GetWorldPosition() const;
};
}
#endif
