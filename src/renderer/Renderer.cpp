#include "Renderer.h"
namespace sablin{

Frame* Renderer::Render(Scene *scene){
    return scene->GetFrame();
}
}
