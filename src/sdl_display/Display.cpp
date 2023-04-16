#include "Display.h"
#include <cassert>
#include <iostream>
namespace sablin{
    Display *Display::singleton_;

    Display::Display(DisplayConfiguration &display_configuration):
            display_configuration_(display_configuration),
            child_display_configuration_(){
       if(Initalize() == -1){
           Destroy();
           exit(-1);
       }
    }

    Display::~Display(){
        Destroy();
    }

    Display* Display::Create(DisplayConfiguration &display_configuration){
        if(Display::singleton_ != nullptr) return Display::singleton_;
        Display::singleton_ = new Display(display_configuration);
        return Display::singleton_;
    }

    Display* Display::GetSingleton(){
#ifdef ASSERT
        assert(Display::singleton_ != nullptr);
#endif
        return Display::singleton_;
    }

    int32_t Display::Initalize(){
        if(SDL_Init(SDL_INIT_VIDEO) == -1){
            std::cout << "SDL_Init Fail" << std::endl;
            return -1;
        }

        window_ = SDL_CreateWindow("Soft-RTR Window",
                    SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    display_configuration_.display_horizontal_size,
                    display_configuration_.display_vertical_size,
                    SDL_WINDOW_SHOWN);

        if(window_ == nullptr){
            std::cout << "SDL_CreateWindow Fail" << std::endl;
            return -1;
        }

        renderer_ = SDL_CreateRenderer(window_, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if(renderer_ == nullptr){
            std::cout << "SDL_CreateRenderer Fail" << std::endl;
            return -1;
        }

        texture_ = SDL_CreateTexture(renderer_, 
                    SDL_PIXELFORMAT_RGBA8888,
                    SDL_TEXTUREACCESS_STREAMING,
                    display_configuration_.display_horizontal_size,
                    display_configuration_.display_vertical_size);

        if(texture_ == nullptr){
            std::cout << "SDL_CreateTexture Fail" << std::endl;
            return -1;
        }

        format_ = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        return 0;
    }

    void Display::Destroy(){
        if(texture_ != nullptr) SDL_DestroyTexture(texture_);
        if(renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
        if(window_ != nullptr) SDL_DestroyWindow(window_);
        SDL_Quit();
        delete singleton_;
        singleton_ = nullptr;
    }
}
