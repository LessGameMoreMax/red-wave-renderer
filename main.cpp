#include "src/defs/SOFT_RTR.h"
#include <SDL2/SDL.h>

using namespace std;
using namespace sablin;

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
    for(int i = 0;i != 90; ++i){
        Display::GetSingleton()->FreshChildDisplayConfiguration(
                ChildDisplayConfiguration{0, 0, &frame});
        Display::GetSingleton()->Draw();
        // SDL_Delay(33);
    }
    return 0;
}
