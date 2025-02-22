#include "../src/defs/SOFT_RTR.h"
#include <SDL2/SDL.h>
#include <time.h>

using namespace std;
using namespace sablin;

Vector4f* ShadeRed();
Vector4f* ShadeGreen();
Vector4f* ShadeBlue();

int main(){
    // bool quit = false;
    // SDL_Event event;

    // while(!quit){
    //     SDL_WaitEvent(&event);
    //     switch(event.type){
    //         case SDL_KEYDOWN:
    //             if(event.key.keysym.sym == SDLK_q){
    //                 SDL_Log("Quit");
    //                 quit = true;
    //             }
    //             break;
    //         case SDL_QUIT:
    //             SDL_Log("Exit");
    //             quit = true;
    //             break;
    //         default:
    //             break;
    //     }
    // }

    int frame_number = 900;
    DisplayConfiguration display_configuration{640, 480};
    Display::Create(display_configuration);

    Frame frame;

    struct timespec time_start = {0, 0};
    struct timespec time_end = {0, 0};
    clock_gettime(CLOCK_REALTIME, &time_start);
    for(int i = 0;i != frame_number; ++i){
        if(i < frame_number / 3)
             frame.FreshColors(ShadeRed());
        else if(i < frame_number / 3 * 2)
             frame.FreshColors(ShadeGreen());
        else
             frame.FreshColors(ShadeBlue());
        Display::GetSingleton()->FreshChildDisplayConfiguration(
                ChildDisplayConfiguration{0, 0, &frame});
        // Display::GetSingleton()->MultiThreadDraw(8);
        Display::GetSingleton()->Draw();
    }
    clock_gettime(CLOCK_REALTIME, &time_end);

    Display::GetSingleton()->Destroy();

    printf("Frame Rate is : %ld\n", frame_number / (time_end.tv_sec - time_start.tv_sec));
    return 0;
}

Vector4f* ShadeRed(){
    Vector4f* temp = new Vector4f[640 * 480];
    for(int i = 0;i != 640 * 480; ++i){
        temp[i].x_ = 1.0f;
    }
    return temp;
}

Vector4f* ShadeGreen(){
    Vector4f* temp = new Vector4f[640 * 480];
    for(int i = 0;i != 640 * 480; ++i){
        temp[i].y_ = 1.0f;
    }
    return temp;
}

Vector4f* ShadeBlue(){
    Vector4f* temp = new Vector4f[640 * 480];
    for(int i = 0;i != 640 * 480; ++i){
        temp[i].z_ = 1.0f;
    }
    return temp;
}
