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
    std::vector<Light*> lights_;
};
}
#endif
