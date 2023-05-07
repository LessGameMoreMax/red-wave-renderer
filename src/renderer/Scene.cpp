#include "Scene.h"
#include <iostream>
namespace sablin{
Scene::Scene():camera_(nullptr){}

Scene::~Scene(){
    for(auto iter = objects_.begin();
            iter != objects_.end(); ++iter)
        delete *iter;
    for(auto iter = lights_.begin();
            iter != lights_.end(); ++iter)
        delete *iter;
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

Camera* Scene::GetCamera() const{
    return camera_;
}

}
