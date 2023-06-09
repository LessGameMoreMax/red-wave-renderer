#include "VertexShade.h"
#include "../math/Compute.h"
#include "../math/Tools.h"
#include "Clip.h"
#include "../threads/MultThreadArgs.h"
#include <iostream>
namespace sablin{

void* VertexShade::Transform(void *arg){
    TransformArgs *temp = static_cast<TransformArgs*>(arg);

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(temp->tid + 1, &mask);
    if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) == -1){
        std::cout << "Could not set CPU affinity!" << std::endl;
    }

    Mesh *mesh = temp->object->GetModel()->mesh_;

    int64_t i;
    while((i = temp->index->load()) != mesh->triangle_pool_size_){
        if(!temp->index->compare_exchange_strong(i, i + 1)) continue;
        
        Triangle *t = &mesh->triangle_pool_[i];
        Primitive *primitive= new Primitive();
        primitive->scene_ = temp->scene;
        primitive->object_ = temp->object;
        primitive->material_ = t->material_;
        primitive->plane_normal_ = ((*temp->NM) * t->normal_).Normalized();

        primitive->world_coord_[0]
            = (*temp->M) * t->vertex_a_.get_local_coord_();
        primitive->world_coord_[1]
            = (*temp->M) * t->vertex_b_.get_local_coord_();
        primitive->world_coord_[2]
            = (*temp->M) * t->vertex_c_.get_local_coord_();

        primitive->project_coord_[0]
            = (*temp->PVM) * t->vertex_a_.get_local_coord_();
        primitive->project_coord_[1]
            = (*temp->PVM) * t->vertex_b_.get_local_coord_();
        primitive->project_coord_[2]
            = (*temp->PVM) * t->vertex_c_.get_local_coord_();

        primitive->uv_coord_[0]
            = t->vertex_a_.get_uv_coord_();
        primitive->uv_coord_[1]
            = t->vertex_b_.get_uv_coord_();
        primitive->uv_coord_[2]
            = t->vertex_c_.get_uv_coord_();

        primitive->vertex_normal_[0]
            = ((*temp->NM) * *t->vertex_a_.normal_).Normalized();
        primitive->vertex_normal_[1]
            = ((*temp->NM) * *t->vertex_b_.normal_).Normalized();
        primitive->vertex_normal_[2]
            = ((*temp->NM) * *t->vertex_c_.normal_).Normalized();

        if(std::abs(primitive->material_->d_ - 1.0f) > FLOAT_ERROR){
            temp->transparent_list->PushFront(primitive);
            continue;
        }

        VertexShade::PerVertexLight(primitive);
    }
    return NULL;
}

void VertexShade::PerVertexLight(Primitive *primitive){
// Implement per vertex light:
// ......
    primitive->color_[0] = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
    primitive->color_[1] = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
    primitive->color_[2] = Vector4f(1.0f, 1.0f, 1.0f, 1.0f);
    
    // primitive->color_[0] = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    // primitive->color_[1] = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    // primitive->color_[2] = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    Clip::PrimitiveClip(primitive);
}
}
