#ifndef FRAME_H
#define FRAME_H
#include <cstdint>
#include "../math/Vectors.h"
namespace sablin{

class Frame{
private:
    int16_t   horizontal_size_;
    int16_t   vertical_size_;
    Vector4f *colors_; 
public:
    explicit Frame();
    explicit Frame(int16_t, int16_t);
    explicit Frame(int16_t, int16_t, Vector4f*);
    Frame(const Frame&) = default;
    Frame& operator=(const Frame&) = default;
    ~Frame();

    int16_t get_horizontal_size_() const;
    int16_t get_vertical_size_() const;
    Vector4f* get_colors_() const;
};
}
#endif
