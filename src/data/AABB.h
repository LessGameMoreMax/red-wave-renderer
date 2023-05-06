#ifndef AABB_H
#define AABB_H
#include "../math/Vectors.h"
namespace sablin{
class AABB{
public:
    Vector4f min_coord_;
    Vector4f max_coord_;
public:
    AABB();
    AABB(const Vector4f&, const Vector4f&);
    AABB(const AABB&) = default;
    AABB& operator=(const AABB&) = default;
    ~AABB() = default;
};
}
#endif
