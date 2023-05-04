#ifndef LOADER_H
#define LOADER_H
#include "../data/Model.h"
#include <string>
#include <map>
namespace sablin{

class Loader{
private:
    static std::string GetParentPath(const std::string&);
    static Vector2f* ParseUVCoord(const std::string&, Mesh*);
    static int64_t ParseVertexCoord(const std::string&);
    static void BuildHEdge(Mesh*);
    static HEdge* GetHEdgePair(Mesh*, const int64_t,
                const Vertex&, const Vertex&);
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
