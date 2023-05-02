#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
namespace sablin{

class Model{
private:
    Material *material_pool_;
    int16_t  material_pool_size_;
public:
    Mesh *mesh_;
public:
    Model(int16_t, Mesh*);
    Model(const Model&) = delete;
    Model& operaor(const Model&) = delete;
    ~Model();
};
}
#endif
