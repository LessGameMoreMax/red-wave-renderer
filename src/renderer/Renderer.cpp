#include "Renderer.h"
#include "VertexShade.h"
namespace sablin{

Frame* Renderer::Render(Scene *scene){
    VertexShade::Transform(scene);
    return scene->GetFrame();
}
}
