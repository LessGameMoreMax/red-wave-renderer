#include "Rasterizer.h"
namespace sablin{
void Rasterizer::PerspectiveDivide(Primitive *primitive){
    for(int8_t i = 0;i != 3; ++i){
        primitive->project_coord_[i].x_ /=
            primitive->project_coord_[i].w_;
        primitive->project_coord_[i].y_ /=
            primitive->project_coord_[i].w_;
        primitive->project_coord_[i].z_ /=
            primitive->project_coord_[i].w_;
    }
    Rasterizer::ViewportTransform(primitive);
}

void Rasterizer::ViewportTransform(Primitive *primitive){
    for(int8_t i = 0;i != 3; ++i){
        primitive->project_coord_[i].x_ =
            (primitive->project_coord_[i].x_ + 1.0f)*
                primitive->scene_->GetFrameWidth() / 2.0f;
        primitive->project_coord_[i].y_ =
            (1.0f - primitive->project_coord_[i].y_)*
                primitive->scene_->GetFrameHeight() / 2.0f;
    }
    Rasterizer::BackfaceCulling(primitive);
}

void Rasterizer::BackfaceCulling(Primitive *primitive){

}


}
