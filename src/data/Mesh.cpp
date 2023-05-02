#include "Mesh.h"
#include <iostream>
namespace sablin{

Mesh::Mesh(const int64_t triangle_pool_size,
        const int64_t coord_pool_size):
        triangle_pool_size_(triangle_pool_size),
        coord_pool_size_(coord_pool_size){
    triangle_pool_ = new Triangle[triangle_pool_size];
    if(triangle_pool_ == nullptr){
        std::cout << "Fail to create triangle pool!" << std::endl;
        exit(-1);
    }

    h_edge_pool_ = new HEdge[triangle_pool_size * 3];
    if(h_edge_pool_ == nullptr){
        std::cout << "Fail to create h_edge pool!" << std::endl;
        delete[] triangle_pool_;
        exit(-1);
    }

    coord_pool_ = new Vector4f[coord_pool_size];
    if(coord_pool_ == nullptr){
        std::cout << "Fail to create coord pool!" << std::endl;
        delete[] h_edge_pool_;
        delete[] triangle_pool_;
        exit(-1);
    }

    vertex_normal_pool_ = new Vector4f[coord_pool_size];
    if(vertex_normal_pool_ == nullptr){
        std::cout << "Fail to create vertex_normal pool!" << std::endl;
        delete[] coord_pool_;
        delete[] h_edge_pool_;
        delete[] triangle_pool_;
        exit(-1);
    }

    vertex_normal_map_ = new Vertex*[coord_pool_size];
    if(vertex_normal_map_ == nullptr){
        std::cout << "Fail to create vertex_normal map!" << std::endl;
        delete[] vertex_normal_pool_;
        delete[] coord_pool_;
        delete[] h_edge_pool_;
        delete[] triangle_pool_;
        exit(-1);
    }    
}

Mesh::~Mesh(){
    delete[] vertex_normal_map_;
    delete[] vertex_normal_pool_;
    delete[] coord_pool_;
    delete[] h_edge_pool_;
    delete[] triangle_pool_;
}




}
