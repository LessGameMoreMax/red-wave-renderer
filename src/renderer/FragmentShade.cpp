#include "FragmentShade.h"
#include "OutputMerger.h"
namespace sablin{

void FragmentShade::PerPixelLight(Fragment *fragment){
//Implement PerPixleLight 
    fragment->color_ = Vector4f{1.0f, 0.0f, 0.0f, 1.0f};
    OutputMerger::DepthTest(fragment);
}

}
