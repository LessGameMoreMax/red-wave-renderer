#include "Renderer.h"
#include "VertexShade.h"
#include "../math/Tools.h"
#include "../math/Compute.h"
#include "MultThreadArgs.h"
#include <iostream>
#include <pthread.h>
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

        int64_t triangle_pool_size_ = object->GetModel()->mesh_->triangle_pool_size_;
        int64_t slice = triangle_pool_size_ / thread_number;
        
        if(slice == 0){
            TransformArgs arg;
            arg.scene = scene;
            arg.begin_index = 0;
            arg.end_index = triangle_pool_size_;
            arg.object = object;
            arg.M = &M;
            arg.NM = &NM;
            arg.PVM = &PVM;
            arg.tid = i;
            VertexShade::Transform((void*)&arg);
        }else{
            pthread_t *threads = new pthread_t[thread_number];
            TransformArgs *args = new TransformArgs[thread_number]; 

            for(int8_t i = 0;i != thread_number; ++i){
                if(i != thread_number - 1){
                    args[i].scene = scene;
                    args[i].begin_index = slice * i;
                    args[i].end_index = slice * (i + 1);
                    args[i].object = object;
                    args[i].M = &M;
                    args[i].NM = &NM;
                    args[i].PVM = &PVM;
                    args[i].tid = i;
                    if(pthread_create(&threads[i], NULL, VertexShade::Transform,
                            (void*)(args + i)) == -1){
                        std::cout << "Create Thread Fail!\n" << std::endl;
                        delete []threads;
                        delete []args;
                        exit(-1);
                    }
                }
                else{
                    args[i].scene = scene;
                    args[i].begin_index = slice * i;
                    args[i].end_index = triangle_pool_size_;
                    args[i].object = object;
                    args[i].M = &M;
                    args[i].NM = &NM;
                    args[i].PVM = &PVM;
                    args[i].tid = i;
                    if(pthread_create(&threads[i], NULL, VertexShade::Transform,
                            (void*)(args + i)) == -1){
                        std::cout << "Create Thread Fail!\n" << std::endl;
                        delete []threads;
                        delete []args;
                        exit(-1);
                    }
                }
            } 

            for(int8_t i = 0;i != thread_number; ++i){
                // if(threads[i]->joinable()){
                //     threads[i]->join();
                //     delete threads[i];
                // }else{
                //     std::cout << "Not Joinable! Render::Render()" << std::endl;
                //     for(int8_t j = i;j != thread_number; ++j)
                //         delete threads[j];
                //     exit(-1);
                // }
                pthread_join(threads[i], NULL);
            }
            delete []threads;
            delete []args;
        }
    }
    return scene->GetFrame();
}
}
