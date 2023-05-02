#ifndef HEDGE_H
#define HEDGE_H
namespace sablin{

class Vertex;
class Triangle;
struct HEdge{
    HEdge    *pair;
    HEdge    *next;
    Vertex   *head;
    Triangle *left;
};
}
#endif
