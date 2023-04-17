#include "src/defs/SOFT_RTR.h"
#include <SDL2/SDL.h>

using namespace std;
using namespace sablin;

Vector4f* ShadeRed();
Vector4f* ShadeGreen();
Vector4f* ShadeBlue();

int main(){
    // bool quit = false;
    // SDL_Event event;

    // DisplayConfiguration display_configuration{640, 480};
    // Display::Create(display_configuration);

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


    DisplayConfiguration display_configuration{640, 480};
    Display::Create(display_configuration);

    Frame frame;
    for(int i = 0;i != 900; ++i){
        // if(i < 300)
        //     frame.FreshColors(ShadeRed());
        // else if(i < 600)
        //     frame.FreshColors(ShadeGreen());
        // else
        //     frame.FreshColors(ShadeBlue());
        Display::GetSingleton()->FreshChildDisplayConfiguration(
                ChildDisplayConfiguration{0, 0, &frame});
        Display::GetSingleton()->Draw();
        // SDL_Delay(33);
    }

    Display::GetSingleton()->Destroy();
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
