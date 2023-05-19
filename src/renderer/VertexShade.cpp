#include "VertexShade.h"
#include "../math/Compute.h"
#include "Clip.h"
#include "MultThreadArgs.h"
#include <iostream>
namespace sablin{

void* VertexShade::Transform(void *arg){
    TransformArgs *temp = static_cast<TransformArgs*>(arg);

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(temp->tid + 2, &mask);
    if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) == -1){
        std::cout << "Could not set CPU affinity!" << std::endl;
    }

    Mesh *mesh = temp->object->GetModel()->mesh_;

    for(int64_t j = temp->begin_index;j != temp->end_index; ++j){
        Triangle *t = &mesh->triangle_pool_[j];
        Primitive primitive;
        primitive.scene_ = temp->scene;
        primitive.object_ = temp->object;
        primitive.material_ = t->material_;
        primitive.plane_normal_ = ((*temp->NM) * t->normal_).Normalized();

        primitive.world_coord_[0]
            = (*temp->M) * t->vertex_a_.get_local_coord_();
        primitive.world_coord_[1]
            = (*temp->M) * t->vertex_b_.get_local_coord_();
        primitive.world_coord_[2]
            = (*temp->M) * t->vertex_c_.get_local_coord_();

        primitive.project_coord_[0]
            = (*temp->PVM) * t->vertex_a_.get_local_coord_();
        primitive.project_coord_[1]
            = (*temp->PVM) * t->vertex_b_.get_local_coord_();
        primitive.project_coord_[2]
            = (*temp->PVM) * t->vertex_c_.get_local_coord_();

        primitive.uv_coord_[0]
            = t->vertex_a_.get_uv_coord_();
        primitive.uv_coord_[1]
            = t->vertex_b_.get_uv_coord_();
        primitive.uv_coord_[2]
            = t->vertex_c_.get_uv_coord_();

        primitive.vertex_normal_[0]
            = ((*temp->NM) * *t->vertex_a_.normal_).Normalized();
        primitive.vertex_normal_[1]
            = ((*temp->NM) * *t->vertex_b_.normal_).Normalized();
        primitive.vertex_normal_[2]
            = ((*temp->NM) * *t->vertex_c_.normal_).Normalized();
        VertexShade::PerVertexLight(&primitive);
    }
    return NULL;
}

void VertexShade::PerVertexLight(Primitive *primitive){
// Implement per vertex light:
// ......
    primitive->color_[0] = Vector4f();
    primitive->color_[1] = Vector4f();
    primitive->color_[2] = Vector4f();
    Clip::PrimitiveClip(primitive);
}
}
