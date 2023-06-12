#include "Renderer.h"
#include "VertexShade.h"
#include "../math/Tools.h"
#include "../math/Compute.h"
#include "../threads/MultThreadArgs.h"
#include "../threads/LockFreeList.h"
#include "Primitive.h"
#include <iostream>
#include <pthread.h>
#include <queue>
namespace sablin{

Frame* Renderer::Render(Scene *scene, const int8_t thread_number){
    scene->GetFrame()->FreshColors();
    scene->FreshDepthBuffer();
    scene->FreshStencilBuffer();

    LockFreeList<Primitive*> list; 

    Matrix4x4f P = scene->GetCamera()->GetProjectMatrix();
    Matrix4x4f V = scene->GetCamera()->GetViewMatrix();

    for(int16_t i = 0;i != scene->ObjectNumber(); ++i){
        Object *object = scene->GetObject(i);
        Matrix4x4f M = object->GetWorldMatrix();
        AABB aabb = object->GetModel()->mesh_->aabb_bounding_box_;
        if(!IsInFov(aabb, P, V, M, scene->GetCamera()->GetNearPlane(),
                    scene->GetCamera()->GetFarPlane()))
            continue;

        Matrix4x4f VM = V * M;
        Matrix4x4f PV = P * V;
        Matrix4x4f PVM = P * V * M;
        Matrix4x4f NM = object->GetNormalWorldMatrix();

        int64_t triangle_pool_size_ = object->GetModel()->mesh_->triangle_pool_size_;
        std::atomic<int64_t> triangle_index;
        triangle_index.store(0);
        
        pthread_t *threads = new pthread_t[thread_number];
        TransformArgs *args = new TransformArgs[thread_number]; 

        for(int8_t i = 0;i != thread_number; ++i){
            args[i].transparent_list = &list;
            args[i].scene = scene;
            args[i].index = &triangle_index;
            args[i].object = object;
            args[i].M = &M;
            args[i].V = &V;
            args[i].PV = &PV;
            args[i].NM = &NM;
            args[i].VM = &VM;
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

        for(int8_t i = 0;i != thread_number; ++i){
            pthread_join(threads[i], NULL);
        }
        delete []threads;
        delete []args;
    }

    //TODO: Implement Transparent algorithm MultiThread Version
    //TODO: Implement Sort Algorithm in list
    list.Sort([](const Primitive *a, const Primitive *b){
        return a->camera_distance_ <= b->camera_distance_;
    });

    while(!list.IsEmpty())
        VertexShade::PerVertexLight(list.PopFront());

    return scene->GetFrame();
}
}
