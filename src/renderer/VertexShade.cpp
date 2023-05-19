#include "VertexShade.h"
#include "../math/Compute.h"
#include "Clip.h"
namespace sablin{

void VertexShade::Transform(Scene *scene, const int32_t begin_index,
        const int32_t end_index, Object *object, const Matrix4x4f &M,
        const Matrix4x4f &NM, const Matrix4x4f &PVM){

    Mesh *mesh = object->GetModel()->mesh_;

    for(int64_t j = begin_index;j != end_index; ++j){
        Triangle *t = &mesh->triangle_pool_[j];
        Primitive primitive;
        primitive.scene_ = scene;
        primitive.object_ = object;
        primitive.material_ = t->material_;
        primitive.plane_normal_ = (NM * t->normal_).Normalized();

        primitive.world_coord_[0]
            = M * t->vertex_a_.get_local_coord_();
        primitive.world_coord_[1]
            = M * t->vertex_b_.get_local_coord_();
        primitive.world_coord_[2]
            = M * t->vertex_c_.get_local_coord_();

        primitive.project_coord_[0]
            = PVM * t->vertex_a_.get_local_coord_();
        primitive.project_coord_[1]
            = PVM * t->vertex_b_.get_local_coord_();
        primitive.project_coord_[2]
            = PVM * t->vertex_c_.get_local_coord_();

        primitive.uv_coord_[0]
            = t->vertex_a_.get_uv_coord_();
        primitive.uv_coord_[1]
            = t->vertex_b_.get_uv_coord_();
        primitive.uv_coord_[2]
            = t->vertex_c_.get_uv_coord_();

        primitive.vertex_normal_[0]
            = (NM * *t->vertex_a_.normal_).Normalized();
        primitive.vertex_normal_[1]
            = (NM * *t->vertex_b_.normal_).Normalized();
        primitive.vertex_normal_[2]
            = (NM * *t->vertex_c_.normal_).Normalized();
        VertexShade::PerVertexLight(&primitive);
    }
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
