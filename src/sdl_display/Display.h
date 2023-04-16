#ifndef DISPLAY_H
#define DISPLAY_H
#include "DisplayStructs.h"
#include <SDL2/SDL.h>
namespace sablin{
class Display{
private:
    static Display *singleton_;
    DisplayConfiguration display_configuration_;
    ChildDisplayConfiguration child_display_configuration_;

    SDL_PixelFormat *format_;
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    SDL_Texture *texture_;
    
    void *pixel;
    int32_t pitch;
    Display():display_configuration_(),child_display_configuration_(),
            format_(nullptr), window_(nullptr), renderer_(nullptr),
            texture_(nullptr), pixel(nullptr), pitch(0){}
    Display(DisplayConfiguration&);

    int32_t Initalize();
    void    Destroy();
public:
    static Display* Create(DisplayConfiguration&);
    static Display* GetSingleton();
    ~Display();
};

}
#endif
