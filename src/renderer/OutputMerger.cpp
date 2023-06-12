#include "OutputMerger.h"
#include "../math/Tools.h"
#include <iostream>
namespace sablin{

void OutputMerger::StencilTest(Fragment *fragment){
    int32_t index = fragment->screen_coord_.y_ *
            fragment->scene_->GetFrameWidth() + fragment->screen_coord_.x_;
    if(fragment->is_shadow_){
        fragment->scene_->stencil_buffer_lock_.lock();
        if(fragment->scene_->GetStencilBuffer()[index] == 0){
            fragment->scene_->GetStencilBuffer()[index] = 1;
            fragment->scene_->stencil_buffer_lock_.unlock();
        }else{
            fragment->scene_->stencil_buffer_lock_.unlock();
            return;
        }
    }
    OutputMerger::DepthTest(fragment);
}

void OutputMerger::DepthTest(Fragment *fragment){
    int32_t index = fragment->screen_coord_.y_ * 
        fragment->scene_->GetFrameWidth() + fragment->screen_coord_.x_;

    if(fragment->depth_ > fragment->scene_->GetDepthBuffer()[index]){
        float alpha = fragment->material_->d_;
        if(std::abs(alpha - 1.0f) > FLOAT_ERROR){
            fragment->scene_->depth_buffer_lock_.lock();
            fragment->scene_->GetFrame()->get_colors_()[index] =
                    fragment->color_ * alpha +
                    fragment->scene_->GetFrame()->get_colors_()[index] * (1.0f -  alpha);
            fragment->scene_->depth_buffer_lock_.unlock();
        }else{
            fragment->scene_->depth_buffer_lock_.lock();
            fragment->scene_->GetFrame()->get_colors_()[index] = fragment->color_;
            fragment->scene_->GetDepthBuffer()[index] = fragment->depth_;
            fragment->scene_->depth_buffer_lock_.unlock();
        }
    }
    //TODO: No lock to speed
    return;
}
}
