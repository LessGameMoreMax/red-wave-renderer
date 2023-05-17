#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "Frame.h"
namespace sablin{

class Scene{
private:
    std::vector<Object*> objects_;
    std::vector<Light*>  lights_;
    Camera*              camera_;
    int16_t              frame_width_;
    int16_t              frame_height_;
    Frame*               frame_;
    float*               depth_buffer_;
public:
    Scene(const int16_t, const int16_t);
    Scene(const Scene&) = default;
    Scene& operator=(const Scene&) = default;
    ~Scene();

    void AddObject(Model *model, const Vector3f &scale = Vector3f(1.0f,1.0f,1.0f), 
                const Vector3f &world_translate_position = Vector3f(0.0f, 0.0f, 0.0f),
                const float local_rotation_angle = 0.0f, 
                const Vector3f &local_rotation_axis = Vector3f(0.0f, 1.0f, 0.0f),
                const Vector3f &world_rotation_position = Vector3f(0.0f, 0.0f, 0.0f),
                const float world_rotation_angle = 0.0f, 
                const Vector3f &world_rotation_axis = Vector3f(0.0f, 1.0f, 0.0f));
    Object* GetObject(const int16_t) const;
    int16_t ObjectNumber() const;

    void AddCamera(const Vector4f &world_position,
                const Vector4f &target_position,
                const Vector4f &up_direction,
                const float near_plane,
                const float far_plane,
                const float vertical_fov_angle);
    Camera* GetCamera() const;

    Light* GetLight(const int16_t) const;
    void AddParallelLight(const Vector4f &direction,
            const Vector4f &color);
    int16_t LightNumber() const;
    
    int16_t GetFrameWidth() const;
    int16_t GetFrameHeight() const;

    Frame* GetFrame() const;
    float* GetDepthBuffer() const;
    void FreshDepthBuffer();
};
}
#endif
