#ifndef FRAGMENT_SHADE_H
#define FRAGMENT_SHADE_H
#include "Fragment.h"
namespace sablin{

class FragmentShade{
public:
    static void PerPixelLight(Fragment*);
    static void Shade(Fragment*);
};
}
#endif
