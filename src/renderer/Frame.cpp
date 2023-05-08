#include "Frame.h"
namespace sablin{

extern int16_t DISPLAY_HORIZONTAL_SIZE;
extern int16_t DISPLAY_VERTICAL_SIZE;

Frame::Frame(): horizontal_size_(DISPLAY_HORIZONTAL_SIZE),
                vertical_size_(DISPLAY_VERTICAL_SIZE),
                colors_ (nullptr){}

Frame::Frame(int16_t horizontal_size, int16_t vertical_size):
                horizontal_size_(horizontal_size),
                vertical_size_(vertical_size),
                colors_(nullptr){}

Frame::Frame(int16_t horizontal_size, int16_t vertical_size,
        Vector4f *colors): horizontal_size_(horizontal_size),
        vertical_size_(vertical_size), colors_(colors){}

Frame::~Frame(){
    if(colors_ != nullptr) delete[] colors_;
}

int16_t Frame::get_horizontal_size_() const{
    return horizontal_size_;
}

int16_t Frame::get_vertical_size_() const{
    return vertical_size_;
}

Vector4f* Frame::get_colors_() const{
    return colors_;
}

void Frame::FreshColors(){
    if(colors_ != nullptr) delete[] colors_;
    colors_ = new Vector4f[horizontal_size_ * vertical_size_];
}

}
