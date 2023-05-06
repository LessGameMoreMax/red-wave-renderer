#include "AABB.h"
namespace sablin{
AABB::AABB():min_coord_(), max_coord_(){}

AABB::AABB(const Vector4f &min_coord, const Vector4f &max_coord):
        min_coord_(min_coord), max_coord_(max_coord){}
}
