#include "ModelPool.h"
namespace sablin{

ModelPool *ModelPool::singleton_;

ModelPool::ModelPool():model_pool_(){}

ModelPool::~ModelPool(){}

ModelPool* ModelPool::Create(){
   if(ModelPool::singleton_ != nullptr) return ModelPool::singleton_; 
   ModelPool::singleton_ = new ModelPool();
   return ModelPool::singleton_;
}

ModelPool* ModelPool::GetSingleton(){
#ifdef ASSERT
    assert(ModelPool::singleton_ != nullptr);
#endif
    return ModelPool::singleton_;
}

void ModelPool::Destroy(){
    for(auto iter = model_pool_.begin();
            iter != model_pool_.end();
            ++iter)
        delete *iter;
    if(singleton_ != nullptr){
        singleton_ = nullptr;
        delete this;
    }
}

void ModelPool::ManageModel(Model *model){
    model_pool_.push_back(model);
}
}
