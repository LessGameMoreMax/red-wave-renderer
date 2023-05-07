#include "Scene.h"
#include <iostream>
namespace sablin{
Scene::Scene(const int16_t frame_width,
            const int16_t frame_height):
        camera_(nullptr),frame_width_(frame_width),
        frame_height_(frame_height){
    objects_.clear();
    lights_.clear();
}

Scene::~Scene(){
    for(auto iter = objects_.begin();
            iter != objects_.end(); ++iter)
        delete *iter;
    for(auto iter = lights_.begin();
            iter != lights_.end(); ++iter)
        delete *iter;
    if(camera_ != nullptr)
        delete camera_;
}


void Scene::AddObject(Model *model, const Vector3f &scale, 
            const Vector3f &world_translate_position,
            const float local_rotation_angle,
            const Vector3f &local_rotation_axis,
            const Vector3f &world_rotation_position,
            const float world_rotation_angle,
            const Vector3f &world_rotation_axis){
    objects_.push_back(new Object(model, scale, world_translate_position,
                local_rotation_angle, local_rotation_axis,
                world_rotation_position, world_rotation_angle,
                world_rotation_axis));
}

Object* Scene::GetObject(const int16_t index) const{
    if(index >= objects_.size()){
        std::cout << "GetObject Beyond!" << std::endl;
        return nullptr;
    }
    return objects_[index];
}

int16_t Scene::ObjectNumber() const{
    return objects_.size();
}

void Scene::AddCamera(const Vector4f &world_position,
                    const Vector4f &target_position,
                    const Vector4f &up_direction,
                    const float near_plane,
                    const float far_plane,
                    const float vertical_fov_angle){
    if(camera_ != nullptr) delete camera_;
    camera_ = new Camera(world_position, target_position,
                up_direction, near_plane, far_plane,
                vertical_fov_angle,
                static_cast<float>(frame_width_)/
                static_cast<float>(frame_height_));
}

Camera* Scene::GetCamera() const{
    return camera_;
}

}
