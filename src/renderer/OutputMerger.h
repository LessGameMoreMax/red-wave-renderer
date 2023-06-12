#ifndef OUTPUT_MERGER_H
#define OUTPUT_MERGER_H
#include "Fragment.h"
namespace sablin{

class OutputMerger{
public:
    static void StencilTest(Fragment*);
    static void DepthTest(Fragment*);
};
}
#endif
