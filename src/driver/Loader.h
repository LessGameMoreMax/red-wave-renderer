#ifndef LOADER_H
#define LOADER_H
#include "../data/Model.h"
#include <string>
#include <map>
namespace sablin{

class Loader{
private:
    static std::string GetParentPath(const std::string&);
    static int8_t JudgeTriangleNumber(const std::string&);
    static void* ParseVertex(const std::string&, int8_t, Mesh*);
public:
    Loader() = delete;
    Loader(const Loader&) = delete;
    Loader& operator=(const Loader&) = delete;
    ~Loader() = default;
public:
    static Model* LoadOBJModel(const std::string&);
    static std::map<std::string, Material*>
        LoadMTLMaterial(const std::string&);
    static Texture* LoadPNGTexture(const std::string&);
};
}
#endif
