#include "Scene.h"
#include "ParallelLight.h"
#include "../math/Tools.h"
#include <iostream>
namespace sablin{
Scene::Scene(const int16_t frame_width,
            const int16_t frame_height):
        camera_(nullptr),frame_width_(frame_width),
        frame_height_(frame_height){
    objects_.clear();
    lights_.clear();
    frame_ = new Frame(frame_width, frame_height);
    depth_buffer_ = new float[frame_width * frame_height];
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
    if(frame_ != nullptr)
        delete frame_;
    if(depth_buffer_ != nullptr)
        delete[] depth_buffer_;
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

void Scene::AddParallelLight(const Vector4f &direction,
        const Vector4f &color){
    lights_.push_back(new ParallelLight(direction, color));
}

Light* Scene::GetLight(const int16_t index) const{
    if(index >= lights_.size()){
        std::cout << "GetLight Beyond!" << std::endl;
        return nullptr;
    }
    return lights_[index];
}

int16_t Scene::LightNumber() const{
    return lights_.size();
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

int16_t Scene::GetFrameWidth() const{
    return frame_width_;
}

int16_t Scene::GetFrameHeight() const{
    return frame_height_;
}

Frame* Scene::GetFrame() const{
    return frame_;
}

float* Scene::GetDepthBuffer() const{
    return depth_buffer_;
}

void Scene::FreshDepthBuffer(){
    for(int32_t i = 0;i != frame_height_ * frame_width_; ++i)
        depth_buffer_[i] = FLOAT_MIN;
}

}
