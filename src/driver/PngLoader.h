#ifndef PNGLOADER_H
#define PNGLOADER_H
#include "../data/Texture.h"
#include <string>
#include <fstream>
#include <vector>
namespace sablin{

class Chunk{
public:
    int32_t length_;
    char type_[4];
    char *data_;
    int32_t crc_;
    
    explicit Chunk();
    Chunk(const Chunk&) = default;
    Chunk& operator=(const Chunk&) = default;
    ~Chunk();
};

class PngLoader{
private:
    static bool IsPNG(std::ifstream&);
    static bool FillChunk(std::ifstream&, Chunk*);
    static void FilterNone(const std::vector<char>&, char*, const int32_t, const int32_t, const int32_t);
    static void FilterSub(const std::vector<char>&, char*, const int32_t, const int32_t, const int32_t);
    static void FilterUp(const std::vector<char>&, char*, const int32_t, const int32_t, const int32_t);
    static void FilterAverage(const std::vector<char>&, char*, const int32_t, const int32_t, const int32_t);
    static void FilterPaeth(const std::vector<char>&, char*, const int32_t, const int32_t, const int32_t);
public:
    static Texture* LoadPNGTexture(const std::string&);
};

}
#endif
