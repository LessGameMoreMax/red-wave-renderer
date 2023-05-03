#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
namespace sablin{

class Model{
private:
    Material *material_pool_;
public:
    Mesh *mesh_;
public:
    Model(Material*, Mesh*);
    Model(const Model&) = delete;
    Model& operaor(const Model&) = delete;
    ~Model();
};
}
#endif
