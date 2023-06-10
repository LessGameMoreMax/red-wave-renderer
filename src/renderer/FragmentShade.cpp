#include "FragmentShade.h"
#include "OutputMerger.h"
#include "../math/Tools.h"
#include "../math/Compute.h"
namespace sablin{
void FragmentShade::BlinnPhongShade(Fragment *fragment){
    Vector4f color{0.0f, 0.0f, 0.0f, 0.0f};
    int16_t light_number = fragment->scene_->LightNumber();
    for(int16_t i = 0;i != light_number; ++i){
        Vector4f light_color = 
            fragment->scene_->GetLight(i)->LightColor(fragment->world_coord_);

        Vector4f ambient{0.1f, 0.1f, 0.1f, 0.0f};

        Vector4f world_normal = fragment->vertex_normal_;
        Vector4f light_direction = 
            fragment->scene_->GetLight(i)->LightDirection(fragment->world_coord_);

        Vector4f diffuse = light_color * Vector4f{fragment->material_->kd_, 0.0f} * 
            Saturate(DotProduct(world_normal, light_direction));

        if(fragment->material_->map_kd_ != nullptr)
            diffuse = diffuse * fragment->material_->map_kd_->Sample(fragment->uv_coord_);

        Vector4f view_direction = (fragment->scene_->GetCamera()->GetWorldPosition() -
            fragment->world_coord_).Normalized();
        Vector4f half_direction = (view_direction + light_direction).Normalized();
        
        Vector4f specular = light_color * Vector4f{fragment->material_->ks_, 0.0f} * 
            std::pow(std::max(0.0f, DotProduct(world_normal, half_direction)), 
                    fragment->material_->ns_);
                    
        color += ambient + diffuse + specular;
    }

    if(light_number != 0)
        fragment->color_ = fragment->color_ * color / light_number;
    else if(light_number == 0 && fragment->material_->map_kd_ != nullptr)
        fragment->color_ = fragment->color_ * fragment->material_->map_kd_->Sample(fragment->uv_coord_);

    fragment->color_.w_ = 1.0f;
}

void FragmentShade::PerPixelLight(Fragment *fragment){
    // BlinnPhongShade(fragment);

// Just For Test Transparent:
    fragment->color_ = Vector4f{fragment->material_->ka_, 1.0f};
// Just For Test Transparent.

    OutputMerger::DepthTest(fragment);
}

}
