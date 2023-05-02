#ifndef MATERIAL_H
#define MATERIAL_H
#include "../math/Vectors.h"
#include "Texture.h"
namespace sablin{

class Material{
public:
    float ns_;
    float ni_;
    float d_;
    float tr_;
    float tf_;
    int8_t illum_;
    sablin::Vector3f ka_;
    sablin::Vector3f kd_;
    sablin::Vector3f ks_;
    sablin::Vector3f ke_;
    Texture *map_ka_;
    Texture *map_kd_;
public:
    Material();
    Material(float, float, float, float, float, int8_t,
            sablin::Vector3f&, sablin::Vector3f&, sablin::Vector3f&,
            sablin::Vector3f&, Texture*, Texture*);
    Material(const Material&) = default;
    Material& operator=(const Material&) = default;
    ~Material();
};
}
#endif
