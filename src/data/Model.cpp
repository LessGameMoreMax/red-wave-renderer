#include "Model.h"
#include <iostream>
namespace sablin{
Model::Model(Material *material_pool,
        Mesh* mesh):
        material_pool_(material_pool),
        mesh_(mesh){}

Model::~Model(){
    delete mesh_;
    delete[] material_pool_;
}

}
