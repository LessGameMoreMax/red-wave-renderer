#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include "../math/Vectors.h"
#include "HEdge.h"
namespace sablin{
class Vertex{
private:
    sablin::Vector4f *local_coord_;
    sablin::Vector2f *uv_coord_;
public:
    sablin::Vector4f *normal_;
    sablin::HEdge    *h_edge_;
public:
    Vertex();
    Vertex(sablin::Vector4f*,sablin::Vector2f*);
    Vertex(const Vertex&) = default;
    Vertex& operator=(const Vertex&) = default;
    ~Vertex() = default;

    sablin::Vector4f get_local_coord_() const;
    void set_local_coord_(sablin::Vector4f&);

    sablin::Vector2f get_uv_coord_() const;
    void set_uv_coord_(sablin::Vector2f&);

    static std::vector<sablin::Triangle*>
        TrianglesOfVertex(const sablin::Vertex&);

    static std::vector<sablin::Vertex*>
        OtherVertexOfVertex(const sablin::Vertex&);

    static bool IsSameCoord(const Vertex&, const Vertex&);
};

}
#endif
