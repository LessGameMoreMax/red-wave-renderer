#include "Model.h"
#include <iostream>
namespace sablin{
Model::Model(int16_t material_pool_size, Mesh* mesh):
        material_pool_size_(material_pool_size),
        mesh_(mesh){
    if(material_pool_size > 0){
        material_pool_ = new Material[material_pool_size];
        if(material_pool_ == nullptr){
            std::cout << "Fail to create material pool!" << std::endl;
            delete[] material_pool_;
            delete mesh_;
            exit(-1);
        }
    }
}

Model::~Model(){
    delete mesh_;
    delete[] material_pool_;
}

}
