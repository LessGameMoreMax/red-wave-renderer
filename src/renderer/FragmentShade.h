#ifndef FRAGMENT_SHADE_H
#define FRAGMENT_SHADE_H
#include "Fragment.h"
namespace sablin{

class FragmentShade{
private:
    static void BlinnPhongShade(Fragment*);    
public:
    static void PerPixelLight(Fragment*);
};
}
#endif
