#include "Triangle.h"
namespace sablin{
Triangle::Triangle():vertex_a_(),vertex_b_(),
        vertex_c_(), material_(nullptr), normal_(),
        h_edge_(nullptr){}

Triangle::Triangle(sablin::Vertex &vertex_a, sablin::Vertex &vertex_b,
            sablin::Vertex &vertex_c, sablin::Material *material):
        vertex_a_(vertex_a), vertex_b_(vertex_b), vertex_c_(vertex_c),
        material_(material), normal_(), h_edge_(nullptr){}

std::vector<Vertex*>
Triangle::VertexesOfTriangle(Triangle &triangle){
    std::vector<Vertex*> result;
    result.push_back(&triangle.vertex_a_);
    result.push_back(&triangle.vertex_b_);
    result.push_back(&triangle.vertex_c_);
    return result;
}


}
