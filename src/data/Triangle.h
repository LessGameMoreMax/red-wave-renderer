#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vertex.h"
#include "Material.h"
namespace sablin{

class Triangle{
public:
    sablin::Vertex    vertex_a_;
    sablin::Vertex    vertex_b_;
    sablin::Vertex    vertex_c_;
    sablin::Material *material_;
    sablin::Vector4f  normal_;
    sablin::HEdge    *h_edge_;
public:
    explicit Triangle();
    explicit Triangle(sablin::Vertex&, sablin::Vertex&,
            sablin::Vertex&, sablin::Material*);
    Triangle(const Triangle&) = default;
    Triangle& operator=(const Triangle&) = default;
    ~Triangle() = default;

    static std::vector<Vertex*>
        VertexesOfTriangle(Triangle&);

    static Vector4f CalculateTriangleNormal(const Triangle&);
};
}
#endif
