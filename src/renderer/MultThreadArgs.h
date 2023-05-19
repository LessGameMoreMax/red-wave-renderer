#ifndef MULTITHREADARGS_H
#define MULTITHREADARGS_H
#include "Scene.h"
namespace sablin{

class TransformArgs{
public:
    Scene *scene;
    int64_t begin_index;
    int64_t end_index;
    Object *object;
    Matrix4x4f *M;
    Matrix4x4f *NM;
    Matrix4x4f *PVM;
    int8_t tid;
};
}
#endif
