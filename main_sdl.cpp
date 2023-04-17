#include <iostream>
#include <SDL2/SDL.h>
#include "src/defs/SOFT_RTR.h"

using namespace std;
using namespace sablin;

int main(){
    // if(SDL_Init(SDL_INIT_VIDEO) == -1){
    //     cout << "Fail to initialize" << endl;
    //     return 0;
    // }
    // cout << "Succeed to initialize" << endl;
    // SDL_Window *window;
    // SDL_Renderer *renderer;
    //
    // window = SDL_CreateWindow("SDL2 Draw Window",
    //             SDL_WINDOWPOS_UNDEFINED,
    //             SDL_WINDOWPOS_UNDEFINED,
    //             640,
    //             480,
    //             SDL_WINDOW_SHOWN);
    //
    // if(window == NULL){
    //     cout << "Could not create window" << endl;
    //     return -1;
    // }
    // renderer = SDL_CreateRenderer(window, -1, 0);
    //
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderClear(renderer);
    // // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // // SDL_RenderDrawPoint(renderer, 10, 10);
    // // SDL_RenderDrawLine(renderer, 5, 1, 20, 5);
    //
    // SDL_RenderPresent(renderer);
    // SDL_Delay(5000);
    // if(renderer){
    //     SDL_DestroyRenderer(renderer);
    // }
    // SDL_Quit();

    void *pixel;
    int pitch;
    SDL_PixelFormat *format;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

    SDL_LockTexture(texture, NULL, &pixel, &pitch);
    cout << pitch << endl;
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    uint32_t color = SDL_MapRGBA(format, 0xff, 0, 0, 0xff);
    // for(int i = 0;i < pitch * 200 / 4; ++i)
    //     ((Uint32*)pixel)[i] = color;
    for(int i = 0;i != 640 * 479; ++i)
        ((uint32_t*)pixel)[i] = color;
    SDL_UnlockTexture(texture);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
