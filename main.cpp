#include "src/defs/SOFT_RTR.h"

using namespace sablin;
using namespace std;

int main(){
    ModelPool::Create();
    Model *cube = 
        Loader::LoadOBJModel(
                "/home/sablin/Projects/soft-rtr/Assets/Models/teapot/teapot.obj");
    // Model *cube = 
    //     Loader::LoadOBJModel(
    //             "/home/sablin/Projects/soft-rtr/Assets/Models/cube/cube.obj");
    ModelPool::GetSingleton()->Destroy();
    return 0;
}
