#include "Camera.h"
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

}


}
