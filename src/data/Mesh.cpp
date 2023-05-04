#include "Mesh.h"
#include <iostream>
namespace sablin{

Mesh::Mesh(const int64_t triangle_pool_size,
        const int64_t coord_pool_size, const int64_t uv_coord_pool_size):
        triangle_pool_size_(triangle_pool_size),
        coord_pool_size_(coord_pool_size),
        uv_coord_pool_size_(uv_coord_pool_size){
    triangle_pool_ = new Triangle[triangle_pool_size];
    if(triangle_pool_ == nullptr)
        PrintError("triangle pool");

    h_edge_pool_ = new HEdge[triangle_pool_size * 3];
    if(h_edge_pool_ == nullptr)
        PrintError("h_edge pool");

    coord_pool_ = new Vector4f[coord_pool_size];
    if(coord_pool_ == nullptr)
        PrintError("coord pool");

    vertex_normal_pool_ = new Vector4f[coord_pool_size];
    if(vertex_normal_pool_ == nullptr)
        PrintError("vertex normal pool");

    vertex_normal_map_ = new Vertex*[coord_pool_size];
    if(vertex_normal_map_ == nullptr)
        PrintError("vertex normal map");
    for(int64_t i = 0;i != coord_pool_size_; ++i)
        vertex_normal_map_[i] = nullptr;
    
    if(uv_coord_pool_size == 0){
        uv_coord_pool_ = nullptr;
        return;
    }
    uv_coord_pool_ = new Vector2f[uv_coord_pool_size];
    if(uv_coord_pool_ == nullptr)
        PrintError("uv coord pool");
}

Mesh::~Mesh(){
    Destroy();
}

void Mesh::Destroy(){
    if(uv_coord_pool_ != nullptr)
        delete[] uv_coord_pool_;
    if(vertex_normal_map_ != nullptr)
        delete[] vertex_normal_map_;
    if(vertex_normal_pool_ != nullptr)
        delete[] vertex_normal_pool_;
    if(coord_pool_ != nullptr)
        delete[] coord_pool_;
    if(h_edge_pool_ != nullptr)
        delete[] h_edge_pool_;
    if(triangle_pool_ != nullptr)
        delete[] triangle_pool_;
}

void Mesh::PrintError(const char *error){
    std::cout << "Fail to create " << error << std::endl;
    Destroy();
    exit(-1);
}


}
