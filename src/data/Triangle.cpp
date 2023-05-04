#include "Triangle.h"
#include "../math/Compute.h"
namespace sablin{
Triangle::Triangle():vertex_a_(),vertex_b_(),
        vertex_c_(), material_(nullptr), normal_(){}
        

Triangle::Triangle(sablin::Vertex &vertex_a, sablin::Vertex &vertex_b,
            sablin::Vertex &vertex_c, sablin::Material *material):
        vertex_a_(vertex_a), vertex_b_(vertex_b), vertex_c_(vertex_c),
        material_(material), normal_(){}

std::vector<Vertex*>
Triangle::VertexesOfTriangle(Triangle &triangle){
    std::vector<Vertex*> result;
    result.push_back(&triangle.vertex_a_);
    result.push_back(&triangle.vertex_b_);
    result.push_back(&triangle.vertex_c_);
    return result;
}

Vector4f
Triangle::CalculateTriangleNormal(const Triangle &triangle){
    Vector4f result = CrossProduct(
        (triangle.vertex_b_.get_local_coord_() - triangle.vertex_a_.get_local_coord_()),
        (triangle.vertex_c_.get_local_coord_() - triangle.vertex_a_.get_local_coord_()));
    return result.Normalized();    
}


}
