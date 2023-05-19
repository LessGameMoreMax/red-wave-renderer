#include "Renderer.h"
#include "VertexShade.h"
namespace sablin{

Frame* Renderer::Render(Scene *scene, const int8_t thread_number){
    scene->GetFrame()->FreshColors();
    scene->FreshDepthBuffer();

    Matrix4x4f P = scene->GetCamera()->GetProjectMatrix();
    Matrix4x4f V = scene->GetCamera()->GetViewMatrix();
    for(int16_t i = 0;i != scene->ObjectNumber(); ++i){
        Object *object = scene->GetObject(i);
        Matrix4x4f M = object->GetWorldMatrix();
        AABB aabb = object->GetModel()->mesh_->aabb_bounding_box_;
        if(!IsInFov(aabb, P, V, M, scene->GetCamera()->GetNearPlane(),
                    scene->GetCamera()->GetFarPlane()))
            continue;

        Matrix4x4f PVM = P * V * M;
        Mesh *mesh = object->GetModel()->mesh_;
        Matrix4x4f NM = object->GetNormalWorldMatrix();
        
        for(int64_t j = 0;j != mesh->triangle_pool_size_; ++j){
            Triangle *t = &mesh->triangle_pool_[j];
            Primitive primitive;
            //PerVertexLight:Fill class primitive
            //......
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
            Clip::PrimitiveClip(&primitive);
        }
    }

    VertexShade::PerVertexLight(scene);
    return scene->GetFrame();
}
}
