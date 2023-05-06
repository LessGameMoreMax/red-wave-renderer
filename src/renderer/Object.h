#ifndef OBJECT_H
#define OBJECT_H
#include "../data/Model.h"
#include "../math/Matrixes.h"
namespace sablin{
class Object{
private:
    Model *model_;
    Matrix4x4f local_scale_;
    Matrix4x4f local_rotation_;
    Matrix4x4f world_translate_;
    Matrix4x4f world_rotation_;
private:
    void BuildLocalScale(const Vector3f&);
    void BuildLocalRotation(const float, const Vector3f&);
    void BuildWorldRotation(const Vector3f&, const float, const Vector3f&);
    void BuildWorldTranslate(const Vector3f&);
    void BuildAnyRotation(const Vector3f&, const float, const Vector3f&, Matrix4x4f*);
public:
    explicit Object(Model *model, const Vector3f &scale = Vector3f(1.0f,1.0f,1.0f),
            const Vector3f &world_translate_position = Vector3f(0.0f, 0.0f, 0.0f),
            const float local_rotation_angle = 0.0f,
            const Vector3f &local_rotation_axis = Vector3f(0.0f, 1.0f, 0.0f),
            const Vector3f &world_rotation_position = Vector3f(0.0f, 0.0f, 0.0f),
            const float world_rotation_angle = 0.0f,
            const Vector3f &world_rotation_axis = Vector3f(0.0f,1.0f,0.0f));
    Object(const Object&) = default;
    Object& operator=(const Object&) = default;
    ~Object() = default;

    void LocalScale(const Vector3f &scale);
    
    void LocalRotate(const float local_rotation_angle,
            const Vector3f &local_rotation_axis);

    void WorldRotate(const Vector3f &world_rotation_position,
            const float world_rotation_angle,
            const Vector3f &world_rotation_axis);

    void WorldTranslate(const Vector3f &world_translate_position);

    Matrix4x4f GetWorldMatrix() const;

    Model* GetModel() const;
};



}
#endif
