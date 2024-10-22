#include "Vertex.h"
#include "Triangle.h"
#include <iostream>
namespace sablin{
Vertex::Vertex():local_coord_(nullptr),uv_coord_(nullptr),
        normal_(), h_edge_(nullptr){}

Vertex::Vertex(sablin::Vector4f *local_coord,
            sablin::Vector2f *uv_coord):
        local_coord_(local_coord), uv_coord_(uv_coord),
        normal_(), h_edge_(nullptr){}

sablin::Vector4f Vertex::get_local_coord_() const{
    return *local_coord_;
}

void Vertex::set_local_coord_(sablin::Vector4f &local_coord){
    *local_coord_ = local_coord;
}

sablin::Vector2f Vertex::get_uv_coord_() const{
    return *uv_coord_;
}

void Vertex::set_uv_coord_(sablin::Vector2f &uv_coord){
    *uv_coord_ = uv_coord;
}

std::vector<sablin::Triangle*>
Vertex::TrianglesOfVertex(const Vertex &vertex){
    std::vector<sablin::Triangle*> triangles;
    HEdge *h_edge_p = vertex.h_edge_;
    do{
        triangles.push_back(h_edge_p->left);
        h_edge_p = h_edge_p->next->pair;
    }while(h_edge_p != vertex.h_edge_);
    return triangles;
}

std::vector<sablin::Vertex*>
Vertex::OtherVertexOfVertex(const Vertex &vertex){
    std::vector<sablin::Vertex*> result;
    std::vector<sablin::Triangle*> triangles = 
            Vertex::TrianglesOfVertex(vertex);
    for(auto iter_t = triangles.begin(); iter_t != triangles.end(); ++iter_t){
        std::vector<sablin::Vertex*> vertexes =
            Triangle::VertexesOfTriangle(**iter_t);
        for(auto iter_v = vertexes.begin(); iter_v != vertexes.end(); ++iter_v)
            if((*iter_v)->get_local_coord_() == vertex.get_local_coord_()){
                result.push_back(*iter_v);
                break;
            }
    }
    return result;
}

bool Vertex::IsSameCoord(const Vertex &a, const Vertex &b){
    return a.local_coord_ == b.local_coord_;
}

Vector4f Vertex::CalculateVertexNormal(const Vertex &vertex){
    std::vector<Triangle*> triangles = Vertex::TrianglesOfVertex(vertex);
    float total_area = 0.0f;
    std::vector<float> areas;
    for(auto iter = triangles.begin(); iter != triangles.end(); ++iter){
        float area = Triangle::CalculateTriangleArea(**iter);
        Vertex *v = (*iter)->GetVertexOfTriangle(vertex.get_local_coord_());
        Triangle *t = Vertex::OppositeTriangle(*v);
        if(t->normal_ == (*iter)->normal_)
            area += Triangle::CalculateTriangleArea(*t);
        areas.push_back(area);
        total_area += area;
    }
    Vector4f result;
    for(int64_t i = 0;i != triangles.size(); ++i)
        result += triangles[i]->normal_ * areas[i] / total_area;
    return result.Normalized();
}

Triangle* Vertex::OppositeTriangle(const Vertex &vertex){
    return vertex.h_edge_->next->next->pair->left;
}


}
