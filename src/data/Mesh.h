#ifndef MESH_H
#define MESH_H
#include "Triangle.h"
#include "../math/Vectors.h"
#include "Vertex.h"
#include "HEdge.h"
#include "AABB.h"
namespace sablin{
class Mesh{
private:
    void Destroy();
    void PrintError(const char*);
public:
    Triangle *triangle_pool_; 
    HEdge    *h_edge_pool_;
    Vector4f *coord_pool_;
    Vector4f *vertex_normal_pool_;
    Vertex*  *vertex_normal_map_;
    Vector2f *uv_coord_pool_;
    AABB     aabb_bounding_box_;

    int64_t  triangle_pool_size_;
    int64_t  coord_pool_size_;
    int64_t  uv_coord_pool_size_;
public:
    Mesh(const int64_t, const int64_t, const int64_t);
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    ~Mesh();
};
}
#endif
