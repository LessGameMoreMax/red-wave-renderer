#include "src/defs/SOFT_RTR.h"
#include <iostream>
using namespace sablin;
using namespace std;

int main(){
//Load The Model
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if(pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) == -1){
        std::cout << "Could not set CPU affinity!" << std::endl;
    }

    ModelPool::Create();
    Model *red = Loader::LoadOBJModel(
            "Assets/Models/transparent_cube/red/cube.obj");

    Model *green = Loader::LoadOBJModel(
            "Assets/Models/transparent_cube/green/cube.obj");

    Model *blue = Loader::LoadOBJModel(
            "Assets/Models/transparent_cube/blue/cube.obj");

    Scene scene(640, 480);
    scene.AddObject(red, Vector3f(1.0f, 0.1f, 1.0f),Vector3f(),
            90.0f , Vector3f(1.0f, 0.0f, 0.0f));

    scene.AddObject(green, Vector3f(1.0f, 0.1f, 1.0f),Vector3f(0.5f, -0.5f, -0.3f),
            90.0f , Vector3f(1.0f, 0.0f, 0.0f));

    scene.AddObject(blue, Vector3f(1.0f, 0.1f, 1.0f),Vector3f(-0.5f, -0.5f, 0.3f),
            90.0f , Vector3f(1.0f, 0.0f, 0.0f));

    scene.AddCamera(Vector4f(0.0f, 0.0f, 10.0f, 0.0f),
                Vector4f(0.0f, 0.0f, 0.0f, 1.0f),
                Vector4f(0.0f, 1.0f, 0.0f, 0.0f),
                1.0f, 1000.0f, 45);
    // scene.AddParallelLight(Vector4f{1.0f, -1.0f, -1.0f, 0.0f},
        // Vector4f{0.8f, 0.8f, 0.8f, 1.0f});
    
    struct timespec time_start = {0, 0};
    struct timespec time_end = {0, 0};
    int frame_number = 900;
    DisplayConfiguration display_configuration{640, 480};
    Display::Create(display_configuration);

    int angle = 0;

    clock_gettime(CLOCK_REALTIME, &time_start);
    for(int i = 0;i != frame_number; ++i){
        // scene.GetObject(0)->LocalRotate(++angle % 360, Vector3f(0.0f, 1.0f, 0.0f));
        Display::GetSingleton()->FreshChildDisplayConfiguration(
                ChildDisplayConfiguration{0, 0,
                    Renderer::Render(&scene, 1)});
        Display::GetSingleton()->Draw();
    }
    clock_gettime(CLOCK_REALTIME, &time_end);


    Display::GetSingleton()->Destroy();
    ModelPool::GetSingleton()->Destroy();

    printf("Frame Rate is : %ld\n", frame_number/
           (time_end.tv_sec - time_start.tv_sec));
    return 0;
}
