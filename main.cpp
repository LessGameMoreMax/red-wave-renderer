#include "src/defs/SOFT_RTR.h"
#include <iostream>
using namespace sablin;
using namespace std;

int main(){
    ModelPool::Create();
    Model *teapot = Loader::LoadOBJModel(
            "/home/sablin/Projects/soft-rtr/Assets/Models/teapot/teapot.obj");
    ModelPool::GetSingleton()->Destroy();
    return 0;
}
