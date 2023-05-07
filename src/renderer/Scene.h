#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "Light.h"
namespace sablin{
class Scene{
private:
    std::vector<Object*> objects_;
    std::vector<Light*>  lights_;
    Camera*              camera_;
    int16_t              frame_width_;
    int16_t              frame_height_;
public:
    Scene();
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

    void AddCamera();
    Camera* GetCamera() const;
};
}
#endif
