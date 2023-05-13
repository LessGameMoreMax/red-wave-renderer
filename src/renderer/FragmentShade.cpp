#include "FragmentShade.h"
#include "OutputMerger.h"
#include "../math/Tools.h"
#include "../math/Compute.h"
namespace sablin{
Vector4f FragmentShade::BlinnPhongShade(Fragment *fragment){
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

        Vector4f view_direction = (fragment->scene_->GetCamera()->GetWorldPosition() -
            fragment->world_coord_).Normalized();
        Vector4f half_direction = (view_direction + light_direction).Normalized();
        
        Vector4f specular = light_color * Vector4f{fragment->material_->ks_, 0.0f} * 
            std::pow(std::max(0.0f, DotProduct(world_normal, half_direction)), 
                    fragment->material_->ns_);
                    
        color += diffuse + specular;
    }
    color.w_ = 1.0f;
    return color;
}

void FragmentShade::PerPixelLight(Fragment *fragment){
//Implement PerPixleLight 
    fragment->color_ = BlinnPhongShade(fragment);
    OutputMerger::DepthTest(fragment);
}

}
