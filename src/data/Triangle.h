#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vertex.h"
#include "Material.h"
namespace sablin{

class Triangle{
private:
    sablin::Vertex    vertex_a_;
    sablin::Vertex    vertex_b_;
    sablin::Vertex    vertex_c_;
    sablin::Material *material_;
    sablin::Vector4f  normal_;
    sablin::HEdge    *h_edge_;
public:
    Triangle();
    Triangle(sablin::Vertex&, sablin::Vertex&,
            sablin::Vertex&, sablin::Material*);
    Triangle(const Triangle&) = default;
    Triangle& operator=(const Triangle&) = default;
    ~Triangle() = default;

    sablin::Vertex* getp_vertex_a_();
    
    sablin::Vertex* getp_vertex_b_();

    sablin::Vertex* getp_vertex_c_();

    sablin::Material* getp_material_() const;

    sablin::Vector4f get_normal_() const;
    void set_normal_(sablin::Vector4f&);

    sablin::HEdge* getp_h_edge_() const;

    static std::vector<Vertex*>
        VertexesOfTriangle(const Triangle&);
    

     
};
}
#endif
