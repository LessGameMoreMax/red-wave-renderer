#include "Renderer.h"
#include "VertexShade.h"
#include "../math/Tools.h"
#include "../math/Compute.h"
#include <thread>
#include <iostream>
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
        Matrix4x4f NM = object->GetNormalWorldMatrix();

        std::thread *threads[thread_number];
        
        for(int8_t i = 0;i != thread_number; ++i){
            threads[i] = new std::thread(VertexShade::PerVertexLight,
                    scene, , , object, M, NM, PVM);
        } 

        for(int8_t i = 0;i != thread_number; ++i){
            if(threads[i]->joinable()){
                threads[i]->join();
                delete threads[i];
            }else{
                std::cout << "Not Joinable! Render::Render()" << std::endl;
                for(int8_t j = i;j != thread_number; ++j)
                    delete threads[j];
                exit(-1);
            }
        }
    }

    return scene->GetFrame();
}
}
