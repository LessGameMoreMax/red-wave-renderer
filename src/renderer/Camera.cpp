#include "Camera.h"
#include "../math/Compute.h"
namespace sablin{
Camera::Camera(const Vector4f &world_position,
            const Vector4f &target_position,
            const Vector4f &up_direction):
        world_position_(world_position),
        target_position_(target_position),
        up_direction_(up_direction){
    FreshViewMatrix();
}

Matrix4x4f Camera::GetViewMatrix() const{
    return view_matrix_;
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


}
