#ifndef MULTITHREADARGS_H
#define MULTITHREADARGS_H
#include "../renderer/Scene.h"
#include "../renderer/Primitive.h"
#include "LockFreeList.h"
#include <atomic>
namespace sablin{

class TransformArgs{
public:
    LockFreeList<Primitive*> *transparent_list;
    Scene *scene;
    std::atomic<int64_t> *index;
    Object *object;
    Matrix4x4f *M;
    Matrix4x4f *NM;
    Matrix4x4f *PVM;
    int8_t tid;
};
}
#endif
