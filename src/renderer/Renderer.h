#ifndef RENDERER_H
#define RENDERER_H
#include "Frame.h"
#include "Scene.h"
namespace sablin{
class Renderer{
public:
    static Frame* Render(Scene*, const int8_t);
};
}
#endif
