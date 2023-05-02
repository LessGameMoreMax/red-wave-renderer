#include "Triangle.h"
namespace sablin{
Triangle::Triangle():vertex_a_(),vertex_b_(),
        vertex_c_(), material_(nullptr), normal_(),
        h_edge_(nullptr){}

Triangle::Triangle(sablin::Vertex &vertex_a, sablin::Vertex &vertex_b,
            sablin::Vertex &vertex_c, sablin::Material *material):
        vertex_a_(vertex_a), vertex_b_(vertex_b), vertex_c_(vertex_c),
        material_(material), normal_(), h_edge_(nullptr){}

Vertex* Triangle::getp_vertex_a_(){
    return &vertex_a_;
}

Vertex* Triangle::getp_vertex_b_(){
    return &vertex_b_;
}

Vertex* Triangle::getp_vertex_c_(){
    return &vertex_c_;
}

Material* Triangle::getp_material_() const{
    return material_;
}

Vector4f Triangle::get_normal_() const{
    return normal_;
}

void Triangle::set_normal_(Vector4f &normal){
    normal_ = normal;
}

HEdge* Triangle::getp_h_edge_() const{
    return h_edge_;
}






}
