#include "Material.h"
namespace sablin{

Material::Material():ns_(0.0f),ni_(0.0f),d_(0.0f),
        tr_(0.0f), tf_(0.0f), illum_(-1), ka_(),kd_(),
        ks_(), ke_(), map_ka_(nullptr),map_kd_(nullptr){}

Material::Material(float ns, float ni, float d, float tr,
        float tf, int8_t illum, sablin::Vector3f &ka,sablin::Vector3f &kd,
        sablin::Vector3f &ks, sablin::Vector3f &ke,
        Texture *map_ka, Texture *map_kd):
        ns_(ns), ni_(ni),d_(d),tr_(tr),tf_(tf),illum_(illum),
        ka_(ka), kd_(kd), ks_(ks), ke_(ke),
        map_ka_(map_ka), map_kd_(map_kd){}

Material::~Material(){
    if(map_ka_ != nullptr)
        delete map_ka_;
    if(map_kd_ != nullptr)
        delete map_kd_;
}







}
