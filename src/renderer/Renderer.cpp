#include "Renderer.h"
#include "VertexShade.h"
namespace sablin{

Frame* Renderer::Render(Scene *scene){
    scene->GetFrame()->FreshColors();
    scene->FreshDepthBuffer();

    VertexShade::PerVertexLight(scene);
    return scene->GetFrame();
}
}
