#ifndef DISPLAYSTRUCTS_H
#define DISPLAYSTRUCTS_H
#include <cstdint>
#include "../math/Vectors.h"
namespace sablin{

struct DisplayConfiguration{
    int16_t display_horizontal_size = 0;
    int16_t display_vertical_size = 0;
};

struct ChildDisplayConfiguration{
    int16_t   left_up_x = 0;
    int16_t   left_up_y = 0;
    int16_t   right_down_x = 0;
    int16_t   right_down_y = 0;
    Vector4f  *colors = 0;
};
}
#endif
