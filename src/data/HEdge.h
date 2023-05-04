#ifndef HEDGE_H
#define HEDGE_H
namespace sablin{

class Vertex;
class Triangle;
struct HEdge{
    HEdge    *pair = nullptr;
    HEdge    *next = nullptr;
    Vertex   *head = nullptr;
    Triangle *left = nullptr;
};
}
#endif
