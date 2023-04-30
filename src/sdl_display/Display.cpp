#include "Display.h"
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>
namespace sablin{

extern int16_t DISPLAY_HORIZONTAL_SIZE;
extern int16_t DISPLAY_VERTICAL_SIZE;

Display *Display::singleton_;

Display::Display(DisplayConfiguration &display_configuration):
        display_configuration_(display_configuration),
        child_display_configuration_(){
   DISPLAY_HORIZONTAL_SIZE = display_configuration_.display_horizontal_size;
   DISPLAY_VERTICAL_SIZE = display_configuration_.display_vertical_size;
   if(Initalize() == -1){
       Destroy();
       exit(-1);
   }
}

Display::~Display(){}

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
    
    if(format_ == nullptr){
        std::cout << "SDL_AllocFormat Fail" << std::endl;
        return -1;
    }
    return 0;
}

void Display::Destroy(){
    if(texture_ != nullptr) SDL_DestroyTexture(texture_);
    if(renderer_ != nullptr) SDL_DestroyRenderer(renderer_);
    if(window_ != nullptr) SDL_DestroyWindow(window_);
    SDL_Quit();
    if(singleton_ != nullptr){
        singleton_ = nullptr;
        delete this;
    }
}

void Display::FreshChildDisplayConfiguration(const ChildDisplayConfiguration &child_display_configuration){
    child_display_configuration_ = child_display_configuration;
}

void Display::Draw(){
    int16_t hori_size = display_configuration_.display_horizontal_size;
    int32_t ch_hori_size = child_display_configuration_.frame->get_horizontal_size_();
    int32_t ch_vert_size = child_display_configuration_.frame->get_vertical_size_();
    Vector4f *colors = child_display_configuration_.frame->get_colors_();
    int32_t start_index = child_display_configuration_.start_y * hori_size + child_display_configuration_.start_x;
    SDL_LockTexture(texture_, nullptr, &pixel_, &pitch_);
    //TODO: accelerated by muti-thread : NO USE!
    for(int32_t i = 0;i != ch_hori_size * ch_vert_size; ++i){
        Vector4f temp = colors[i] * 255.0f;
        ((uint32_t*)pixel_)[start_index + i / ch_hori_size * hori_size + i % ch_hori_size] =
            SDL_MapRGBA(format_, temp.x_, temp.y_, temp.z_, 0xff);
    }
    SDL_UnlockTexture(texture_);
    
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);
}

void FillPixels(const int32_t start_index, const int16_t pi_hori_size, const int16_t pi_vert_size,
            const Vector4f *colors, const int32_t color_index, const int16_t hori_size, const int32_t ch_hori_size,
            void* pixel, SDL_PixelFormat *format){
    int32_t total_size = pi_hori_size * pi_vert_size;
    for(int32_t i = 0;i != total_size; ++i){
        Vector4f temp = colors[color_index + i / pi_hori_size * ch_hori_size + i % pi_hori_size] * 255.0f;
        ((uint32_t*)pixel)[start_index + i / pi_hori_size * hori_size + i % pi_hori_size] =
            SDL_MapRGBA(format, temp.x_, temp.y_, temp.z_, 0xff);
    }
    return;
}

void Display::MultiThreadDraw(const int16_t thread_number){
    if(thread_number % 2 != 0){
        std::cout << "Multi thread number must be even!\n" << std::endl;
        std::cout << "Now Running single thread!\n" << std::endl;
        return Draw();
    }

    int8_t half_thread_number = thread_number / 2;
    int16_t hori_size = display_configuration_.display_horizontal_size;
    int32_t ch_hori_size = child_display_configuration_.frame->get_horizontal_size_();
    int32_t ch_vert_size = child_display_configuration_.frame->get_vertical_size_();
    int32_t pi_hori_size = ch_hori_size / half_thread_number;
    int32_t pi_vert_size = ch_vert_size / 2;
    Vector4f *colors = child_display_configuration_.frame->get_colors_();
    
    std::thread *threads[thread_number];

    SDL_LockTexture(texture_, nullptr, &pixel_, &pitch_);
    int32_t start_index = child_display_configuration_.start_y * hori_size + child_display_configuration_.start_x;
    //TODO: Implement a thread pool!
    for(int8_t i = 0;i != thread_number; ++i){
        threads[i] = new std::thread(FillPixels, 
                 start_index + i % half_thread_number * pi_hori_size + i / half_thread_number * pi_vert_size * hori_size,
                 pi_hori_size, pi_vert_size, colors, i%half_thread_number*pi_hori_size + i/half_thread_number*pi_vert_size*ch_hori_size,
                 hori_size, ch_hori_size, pixel_, format_);
    }
    for(int8_t i = 0;i != thread_number; ++i){
        if(threads[i]->joinable()){
            threads[i]->join();
            delete threads[i];
        }
        else{
            std::cout << "Not Joinable!" << std::endl;;
            for(int8_t j = i;j != thread_number; ++j)
                delete threads[j];
            Destroy();
            exit(-1);
        }
    }

    SDL_UnlockTexture(texture_);
    
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);
}

}
