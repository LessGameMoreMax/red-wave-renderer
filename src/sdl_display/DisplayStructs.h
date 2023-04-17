#ifndef DISPLAYSTRUCTS_H
#define DISPLAYSTRUCTS_H
#include <cstdint>
#include "../math/Vectors.h"
#include "../renderer/Frame.h"
namespace sablin{

struct DisplayConfiguration{
    int16_t display_horizontal_size = 0;
    int16_t display_vertical_size = 0;
};

struct ChildDisplayConfiguration{
    int16_t start_x = 0;
    int16_t start_y = 0;
    Frame *frame = nullptr;
};
}
#endif
