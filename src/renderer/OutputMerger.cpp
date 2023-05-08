#include "OutputMerger.h"
namespace sablin{

void OutputMerger::DepthTest(Fragment *fragment){
    int32_t index = fragment->screen_coord_.y_ * 
        fragment->scene_->GetFrameWidth() + fragment->screen_coord_.x_;
    if(fragment->depth_ > fragment->scene_->GetDepthBuffer()[index])
        fragment->scene_->GetFrame()->get_colors_()[index] =
            fragment->color_;
}
}
