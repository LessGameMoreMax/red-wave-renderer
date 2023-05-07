#include "Object.h"
#include "../math/Compute.h"
#include "../math/Tools.h"
#include <assert.h>
namespace sablin{
Object::Object(Model *model, const Vector3f &scale,
            const Vector3f &world_translate_position,
            const float local_rotation_angle,
            const Vector3f &local_rotation_axis,
            const Vector3f &world_rotation_position,
            const float world_rotation_angle,
            const Vector3f &world_rotation_axis):
        model_(model){
#ifdef ASSERT
    assert(model_ != nullptr);
#endif
    BuildLocalScale(scale);
    BuildWorldTranslate(world_translate_position);
    BuildLocalRotation(local_rotation_angle,
            local_rotation_axis);
    BuildWorldRotation(world_rotation_position,
            world_rotation_angle,
            world_rotation_axis);
            
}

void Object::BuildLocalScale(const Vector3f &scale){
    local_scale_.e00_ = scale.x_;
    local_scale_.e01_ = 0.0f;
    local_scale_.e02_ = 0.0f;
    local_scale_.e03_ = 0.0f;
    local_scale_.e10_ = 0.0f;
    local_scale_.e11_ = scale.y_;
    local_scale_.e12_ = 0.0f;
    local_scale_.e13_ = 0.0f;
    local_scale_.e20_ = 0.0f;
    local_scale_.e21_ = 0.0f;
    local_scale_.e22_ = scale.z_;
    local_scale_.e23_ = 0.0f;
    local_scale_.e30_ = 0.0f;
    local_scale_.e31_ = 0.0f;
    local_scale_.e32_ = 0.0f;
    local_scale_.e33_ = 1.0f;
}

void Object::BuildLocalRotation(const float local_rotation_angle,
            const Vector3f &local_rotation_axis){
    BuildAnyRotation(Vector3f(0.0f, 0.0f, 0.0f), local_rotation_angle,
                local_rotation_axis, &local_rotation_);
}

void Object::BuildWorldRotation(const Vector3f &world_rotation_position,
            const float world_rotation_angle,
            const Vector3f &world_rotation_axis){
    BuildAnyRotation(world_rotation_position,
            world_rotation_angle,
            world_rotation_axis, &world_rotation_);
}

void Object::BuildWorldTranslate(const Vector3f &world_position){
    world_translate_.e00_ = 1.0f;
    world_translate_.e01_ = 0.0f;
    world_translate_.e02_ = 0.0f;
    world_translate_.e03_ = world_position.x_;

    world_translate_.e10_ = 0.0f;
    world_translate_.e11_ = 1.0f;
    world_translate_.e12_ = 0.0f;
    world_translate_.e13_ = world_position.y_;

    world_translate_.e20_ = 0.0f;
    world_translate_.e21_ = 0.0f;
    world_translate_.e22_ = 1.0f;
    world_translate_.e23_ = world_position.z_;

    world_translate_.e30_ = 0.0f;
    world_translate_.e31_ = 0.0f;
    world_translate_.e32_ = 0.0f;
    world_translate_.e33_ = 1.0f;
}

void Object::BuildAnyRotation(
            const Vector3f &position, const float angle, 
            const Vector3f &axis, Matrix4x4f *matrix){
    Matrix4x4f translate{
        1.0f, 0.0f, 0.0f, -position.x_,
        0.0f, 1.0f, 0.0f, -position.y_,
        0.0f, 0.0f, 1.0f, -position.z_,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    Matrix4x4f re_translate{
        1.0f, 0.0f, 0.0f, position.x_,
        0.0f, 1.0f, 0.0f, position.y_,
        0.0f, 0.0f, 1.0f, position.z_,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    double radian = AngleToRadian(angle);
    double c = std::cos(radian);
    double s = std::sin(radian);

    double x = axis.x_;
    double y = axis.y_;
    double z = axis.z_;

    Matrix4x4f rotation;
    rotation.e00_ = c + (1.0f - c) * x * x;
    rotation.e10_ = (1.0f - c) * x * y + s * z;
    rotation.e20_ = (1.0f - c) * x * z - s * y;
    rotation.e03_ = 0.0f;
    
    rotation.e01_ = (1.0f - c) * x * y - s * z;
    rotation.e11_ = c + (1.0f - c) * y * y;
    rotation.e21_ = (1.0f - c) * y * z + s * x;
    rotation.e13_ = 0.0f;

    rotation.e02_ = (1.0f - c) * x * z + s * y;
    rotation.e12_ = (1.0f - c) * y * z - s * x;
    rotation.e22_ = c + (1.0f - c) * z * z;
    rotation.e23_ = 0.0f;

    rotation.e30_ = 0.0f;
    rotation.e31_ = 0.0f;
    rotation.e32_ = 0.0f;
    rotation.e33_ = 1.0f;

    *matrix = re_translate * rotation * translate;
}

void Object::LocalScale(const Vector3f &scale){
    BuildLocalScale(scale);
}

void Object::LocalRotate(const float local_rotation_angle,
            const Vector3f &local_rotation_axis){
    BuildLocalRotation(local_rotation_angle,
            local_rotation_axis);
}

void Object::WorldRotate(const Vector3f &world_rotation_position,
            const float world_rotation_angle,
            const Vector3f &world_rotation_axis){
    BuildWorldRotation(world_rotation_position, world_rotation_angle,
            world_rotation_axis);
}

void Object::WorldTranslate(const Vector3f &world_translate_position){
    BuildWorldTranslate(world_translate_position);
}

Matrix4x4f Object::GetWorldMatrix() const{
   return world_rotation_ * world_translate_ *
            local_rotation_ * local_scale_;
}

Matrix4x4f Object::GetNormalWorldMatrix() const{
    Matrix4x4f local_scale_it;
    local_scale_it.e00_ = 1.0f / local_scale_.e00_;
    local_scale_it.e01_ = 0.0f;
    local_scale_it.e02_ = 0.0f;
    local_scale_it.e03_ = 0.0f;

    local_scale_it.e10_ = 0.0f;
    local_scale_it.e11_ = 1.0f / local_scale_.e11_;
    local_scale_it.e12_ = 0.0f;
    local_scale_it.e13_ = 0.0f;

    local_scale_it.e20_ = 0.0f;
    local_scale_it.e21_ = 0.0f;
    local_scale_it.e22_ = 1.0f / local_scale_.e22_;
    local_scale_it.e23_ = 0.0f;

    local_scale_it.e30_ = 0.0f;
    local_scale_it.e31_ = 0.0f;
    local_scale_it.e32_ = 0.0f;
    local_scale_it.e33_ = 1.0f / local_scale_.e33_;
    return world_rotation_ * local_rotation_
            * local_scale_it;
}

Model* Object::GetModel() const{
    return model_;
}

}
