#include "src/defs/SOFT_RTR.h"
#include <iostream>

using namespace sablin;
using namespace std;

void PrintVertexInfo(Vertex&);
void PrintMaterialInfo(Material*);
void PrintVector3f(Vector3f&);

int main(){
    ModelPool::Create();
    Model *cube = 
        Loader::LoadOBJModel(
                "Assets/Models/teapot/teapot.obj");
    // Model *cube = 
    //     Loader::LoadOBJModel(
    //             "/home/sablin/Projects/soft-rtr/Assets/Models/cube/cube.obj");

    for(int i = 0;i != cube->mesh_->triangle_pool_size_; ++i){
        Triangle t = cube->mesh_->triangle_pool_[i];
        std::cout << "Triangle: " << i << std::endl;
        std::cout << "Triangle normal: " << t.normal_.x_  << " "
            << t.normal_.y_ << " " << t.normal_.z_ << " "
            << t.normal_.w_ << std::endl;
        //PrintMaterialInfo(t.material_);
        PrintVertexInfo(t.vertex_a_);
        PrintVertexInfo(t.vertex_b_);
        PrintVertexInfo(t.vertex_c_);
        std::cout << std::endl;
    }
    ModelPool::GetSingleton()->Destroy();
    return 0;
}

void PrintVertexInfo(Vertex &v){
    std::cout << "---------------Vertex-------------" << std::endl;
    std::cout << "Vertex coord: " <<
        v.get_local_coord_().x_ << " " <<
        v.get_local_coord_().y_ << " " <<
        v.get_local_coord_().z_ << " " <<
        v.get_local_coord_().w_ << std::endl;
    std::cout << "Vertex uv coord: " <<
        v.get_uv_coord_().x_ << " " <<
        v.get_uv_coord_().y_ << std::endl;
}

void PrintMaterialInfo(Material *m){
    std::cout << "------------Material--------------" << std::endl;
    std::cout << m->ns_ << std::endl;
    std::cout << m->ni_ << std::endl;
    std::cout << m->d_ << std::endl;
    printf("%d\n", m->illum_);
    PrintVector3f(m->ka_);
    PrintVector3f(m->kd_);
    PrintVector3f(m->ke_);
    PrintVector3f(m->ks_);
    std::cout << m->map_ka_ << std::endl;
    std::cout << m->map_kd_ << std::endl;
}

void PrintVector3f(Vector3f &v){
    std::cout << v.x_ << " " << v.y_ << " " << v.z_ << std::endl;
}
