#include "src/defs/SOFT_RTR.h"
#include <iostream>

using namespace std;
using namespace sablin;

int main(){
    ModelPool::Create();
    Model *cube = Loader::LoadOBJModel(
                "/home/sablin/Projects/soft-rtr/Assets/Models/dragon/dragon.obj");
    // Model *cube = Loader::LoadOBJModel(
    //             "/home/sablin/Projects/soft-rtr/Assets/Models/teapot/teapot.obj");

    // for(int64_t i = 0;i != cube->mesh_->triangle_pool_size_; ++i){
    //     std::cout << "Triangle: " << i << std::endl;
    //     Triangle *t = cube->mesh_->triangle_pool_ + i;
    //     std::cout << t->vertex_a_.normal_->x_ << std::endl;
    //     std::cout << t->vertex_a_.normal_->y_ << std::endl;
    //     std::cout << t->vertex_a_.normal_->z_ << std::endl;
    //     std::cout << t->vertex_a_.normal_->w_ << std::endl;
    //     std::cout << std::endl;
    //     std::cout << t->vertex_b_.normal_->x_ << std::endl;
    //     std::cout << t->vertex_b_.normal_->y_ << std::endl;
    //     std::cout << t->vertex_b_.normal_->z_ << std::endl;
    //     std::cout << t->vertex_b_.normal_->w_ << std::endl;
    //     std::cout << std::endl;
    //     std::cout << t->vertex_c_.normal_->x_ << std::endl;
    //     std::cout << t->vertex_c_.normal_->y_ << std::endl;
    //     std::cout << t->vertex_c_.normal_->z_ << std::endl;
    //     std::cout << t->vertex_c_.normal_->w_ << std::endl;
    // }

    ModelPool::GetSingleton()->Destroy();
    return 0;
}
