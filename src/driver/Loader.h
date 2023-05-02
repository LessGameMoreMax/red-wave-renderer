#ifndef LOADER_H
#define LOADER_H
#include "../data/Model.h"
#include <string>
namespace sablin{

class Loader{
public:
    Loader() = delete;
    Loader(const Loader&) = delete;
    Loader& operator=(const Loader&) = delete;
    ~Loader() = default;
public:
    static Model* LoadOBJModel(const std::string&);
    static Material* LoadMTLMaterial(const std::string&);
    static Texture* LoadPNGTexture(const std::string&);
};
}
#endif
