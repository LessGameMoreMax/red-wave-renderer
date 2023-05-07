#include "Camera.h"
#include "../math/Compute.h"
#include "../math/Tools.h"
namespace sablin{
Camera::Camera(const Vector4f &world_position,
            const Vector4f &target_position,
            const Vector4f &up_direction,
            const float near_plane,
            const float far_plane,
            const float vertical_fov_angle,
            const float aspect_ratio):
        world_position_(world_position),
        target_position_(target_position),
        up_direction_(up_direction),
        near_plane_(near_plane),
        far_plane_(far_plane),
        vertical_fov_radian_(AngleToRadian(vertical_fov_angle)),
        aspect_ratio_(aspect_ratio){
    FreshViewMatrix();
    FreshProjectMatrix();
}

Matrix4x4f Camera::GetViewMatrix() const{
    return view_matrix_;
}

Matrix4x4f Camera::GetProjectMatrix() const{
    return project_matrix_;
}

void Camera::FreshViewMatrix(){
    Vector4f w = (world_position_ - target_position_) /
            (world_position_ - target_position_).Norm();
    Vector4f u = CrossProduct(up_direction_, w) /
            CrossProduct(up_direction_, w).Norm();
    Vector4f v = CrossProduct(w, u);

    view_matrix_.e00_ = u.x_;
    view_matrix_.e01_ = u.y_;
    view_matrix_.e02_ = u.z_;
    view_matrix_.e03_ = -DotProduct(world_position_, u);

    view_matrix_.e10_ = v.x_;
    view_matrix_.e11_ = v.y_;
    view_matrix_.e12_ = v.z_;
    view_matrix_.e13_ = -DotProduct(world_position_, v);

    view_matrix_.e20_ = w.x_;
    view_matrix_.e21_ = w.y_;
    view_matrix_.e22_ = w.z_;
    view_matrix_.e23_ = -DotProduct(world_position_, w);

    view_matrix_.e30_ = 0.0f;
    view_matrix_.e31_ = 0.0f;
    view_matrix_.e32_ = 0.0f;
    view_matrix_.e33_ = 1.0f;
}

void Camera::FreshProjectMatrix(){
    project_matrix_.e00_ = -1.0f/(aspect_ratio_ * std::tan(vertical_fov_radian_/2.0f));
    project_matrix_.e01_ = 0.0f;
    project_matrix_.e02_ = 0.0f;
    project_matrix_.e03_ = 0.0f;

    project_matrix_.e10_ = 0.0f;
    project_matrix_.e11_ = -1.0f/std::tan(vertical_fov_radian_/2.0f);
    project_matrix_.e12_ = 0.0f;
    project_matrix_.e13_ = 0.0f;

    project_matrix_.e20_ = 0.0f;
    project_matrix_.e21_ = 0.0f;
    project_matrix_.e22_ = (far_plane_ + near_plane_) / (near_plane_ - far_plane_);
    project_matrix_.e23_ = 2.0f * near_plane_ * far_plane_ / (near_plane_ - far_plane_);

    project_matrix_.e30_ = 0.0f;
    project_matrix_.e31_ = 0.0f;
    project_matrix_.e32_ = 1.0f;
    project_matrix_.e33_ = 0.0f;
}

float Camera::GetNearPlane() const{
    return near_plane_;
}

float Camera::GetFarPlane() const{
    return far_plane_;
}

}
