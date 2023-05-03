#ifndef MODEL_POOL_H
#define MODEL_POOL_H
#include <vector>
#include "Model.h"
namespace sablin{
class ModelPool{
private:
    static ModelPool *singleton_;
    std::vector<Model*> model_pool_;
    ModelPool();
public:
    ModelPool(const ModelPool&) = delete;
    ModelPool& operator=(const ModelPool&) = delete;
    ~ModelPool();
    static ModelPool* GetSingleton();
    static ModelPool* Create();
    void Destroy();

    void ManageModel(Model*);
    Model* GetModel(int16_t) const;
    int16_t ModelPoolSize() const;
};
}
#endif
