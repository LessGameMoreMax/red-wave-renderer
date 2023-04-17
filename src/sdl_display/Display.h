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
    
    void *pixel_;
    int32_t pitch_;
    Display(DisplayConfiguration&);

    int32_t Initalize();
public:
    static Display* Create(DisplayConfiguration&);
    void    Destroy();
    static Display* GetSingleton();
    ~Display();
    void FreshChildDisplayConfiguration(const ChildDisplayConfiguration&);
    void Draw();
};

}
#endif
