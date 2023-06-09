#include "Rasterizer.h"
#include "../math/Vectors.h"
#include "../math/Tools.h"
#include "../math/Compute.h"
#include "Fragment.h"
#include "FragmentShade.h"
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
    Vector2f a{
        primitive->project_coord_[1].x_ - primitive->project_coord_[0].x_,
        primitive->project_coord_[1].y_ - primitive->project_coord_[0].y_};
    Vector2f b{
        primitive->project_coord_[2].x_ - primitive->project_coord_[0].x_,
        primitive->project_coord_[2].y_ - primitive->project_coord_[0].y_};
    if(a.x_ * b.y_ - a.y_ * b.x_ > 0.0f) return;
    Rasterizer::Rasterization(primitive);
}

void Rasterizer::Rasterization(Primitive *primitive){
    Vector2i min_screen_pos{INT16_T_MAX, INT16_T_MAX};
    Vector2i max_screen_pos{INT16_T_MIN, INT16_T_MIN};
    BoundingBoxScreen(primitive, &min_screen_pos, &max_screen_pos);

    Vector2f vec02{
        primitive->project_coord_[2].x_ - primitive->project_coord_[0].x_,
        primitive->project_coord_[2].y_ - primitive->project_coord_[0].y_};
    Vector2f vec21{
        primitive->project_coord_[1].x_ - primitive->project_coord_[2].x_,
        primitive->project_coord_[1].y_ - primitive->project_coord_[2].y_};
    Vector2f vec10{
        primitive->project_coord_[0].x_ - primitive->project_coord_[1].x_,
        primitive->project_coord_[0].y_ - primitive->project_coord_[1].y_};
    
    float total_area = CrossProduct(vec02, Vector2f{-vec10.x_, -vec10.y_});

    for(int16_t i = min_screen_pos.x_; i != max_screen_pos.x_; ++i)
        for(int16_t j = min_screen_pos.y_; j != max_screen_pos.y_; ++j){
            Vector2f pixel_coord{i + 0.5f, j + 0.5f};
            Vector2f vec0p{
                pixel_coord.x_ - primitive->project_coord_[0].x_,
                pixel_coord.y_ - primitive->project_coord_[0].y_};
            Vector2f vec1p{
                pixel_coord.x_ - primitive->project_coord_[1].x_,
                pixel_coord.y_ - primitive->project_coord_[1].y_};
            Vector2f vec2p{
                pixel_coord.x_ - primitive->project_coord_[2].x_,
                pixel_coord.y_ - primitive->project_coord_[2].y_};

            float judge_one = CrossProduct(vec02, vec0p);
            if(judge_one < 0) continue;
            float judge_two = CrossProduct(vec21, vec2p);
            if(judge_two < 0) continue;
            float judge_three = CrossProduct(vec10, vec1p);
            if(judge_three < 0) continue;

            float a = judge_two / total_area;
            float b = judge_one / total_area;
            float c = judge_three / total_area;

            Fragment fragment;
            fragment.material_ = primitive->material_;
            fragment.scene_ = primitive->scene_;

            float za = primitive->project_coord_[0].z_;
            float zb = primitive->project_coord_[1].z_;
            float zc = primitive->project_coord_[2].z_;

            fragment.depth_ = 1.0f / 
                (a / za +
                 b / zb +
                 c / zc);

            fragment.world_coord_ =
                (primitive->world_coord_[0] * a / za +
                 primitive->world_coord_[1] * b / zb +
                 primitive->world_coord_[2] * c / zc) *
                fragment.depth_;

            fragment.world_coord_ =
                (primitive->world_coord_[0] * a / za +
                 primitive->world_coord_[1] * b / zb +
                 primitive->world_coord_[2] * c / zc) *
                fragment.depth_;

            fragment.uv_coord_ =
                (primitive->uv_coord_[0] * a / za +
                 primitive->uv_coord_[1] * b / zb +
                 primitive->uv_coord_[2] * c / zc) *
                fragment.depth_;

            fragment.vertex_normal_ =
                (primitive->vertex_normal_[0] * a / za +
                 primitive->vertex_normal_[1] * b / zb +
                 primitive->vertex_normal_[2] * c / zc) *
                fragment.depth_;

            fragment.screen_coord_.x_ = i;
            fragment.screen_coord_.y_ = j;

            FragmentShade::PerPixelLight(&fragment);
        }
}

}
