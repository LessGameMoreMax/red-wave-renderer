#include "src/defs/SOFT_RTR.h"
#include <iostream>

using namespace std;
using namespace sablin;

int main(){
    ModelPool::Create();
    Model *cube = Loader::LoadOBJModel(
                "/home/sablin/Projects/soft-rtr/Assets/Models/cube/cube.obj");
    // Model *teapot = Loader::LoadOBJModel(
    //             "/home/sablin/Projects/soft-rtr/Assets/Models/teapot/teapot.obj");

    ModelPool::GetSingleton()->Destroy();
    return 0;
}
