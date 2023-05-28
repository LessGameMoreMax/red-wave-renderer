#include "PngLoader.h"
#include "../math/Tools.h"
#include <cstring>
#include <iostream>
#include <zlib.h>
namespace sablin{

Chunk::Chunk(): length_(0), data_(nullptr), crc_(0){}

Chunk::~Chunk(){
    if(data_ != nullptr)
        delete[] data_;
}

Texture* PngLoader::LoadPNGTexture(const std::string &file_path){
    std::ifstream png_file;
    png_file.open(file_path, std::ios::in);
    if(!png_file.is_open()){
        std::cout << "Fail to open png file: " << file_path << std::endl;
        exit(-1);
    }

// Judge Is Png:
    if(!IsPNG(png_file)){
        std::cout << "Not PNG!" << std::endl;
        exit(-1);
    }

// Fill IHDR Chunk:
    int32_t width = 0;
    int32_t height = 0;
    int8_t bit_depth = 0;
    int8_t color_type = 0;
    int8_t filter_method = 0;
    {
        char type[]{'I', 'H', 'D', 'R'};
        Chunk ihdr;
        FillChunk(png_file, &ihdr);
        if(memcmp(type, ihdr.type_, 4) != 0){
            std::cout << "Not IHDR!" << std::endl;
            exit(-1);
        }
        sablin::MemCopyRev(&width, ihdr.data_, 4);
        sablin::MemCopyRev(&height, ihdr.data_ + 4, 4);
        
        bit_depth = ihdr.data_[8];
        color_type = ihdr.data_[9];
        filter_method = ihdr.data_[11];

        // TODO: Implement Interlacing Adam7
        // Only Perlacing:
        if(ihdr.data_[12] != 0x00){
            std::cout << "Not Perlacing!" << std::endl;
            exit(-1);
        }
    }

//debug---------
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "color_type: " << (int16_t)color_type << std::endl;
    std::cout << "bit_depth: " << (int16_t)bit_depth << std::endl;
//debug---------
// Fill Chunks:
    char plte_type[]{'P', 'L', 'T', 'E'};
    Vector4f *plte = nullptr;

    char idat_type[]{'I', 'D', 'A', 'T'};
    std::vector<Chunk*> idats;

    char trns_type[]{'t', 'R', 'N', 'S'};
    while(true){
        Chunk temp;
        if(!FillChunk(png_file, &temp)) break;
        if(std::memcmp(plte_type, temp.type_, 4) == 0){
            if(plte != nullptr){
                std::cout << "Wrong PLTE!" << std::endl;
                exit(-1);
            }
            plte = new Vector4f[temp.length_/3];
            for(int32_t i = 0;i != temp.length_/3; ++i){
               plte[i].x_ = (uint8_t)temp.data_[i * 3 + 0] / 255.0f;
               plte[i].y_ = (uint8_t)temp.data_[i * 3 + 1] / 255.0f;
               plte[i].z_ = (uint8_t)temp.data_[i * 3 + 2] / 255.0f;
               plte[i].w_ = 1.0f;
            }
        }else if(std::memcmp(idat_type, temp.type_, 4) == 0){
            idats.push_back(new Chunk(temp));
            temp.data_ = nullptr;
        }else if(std::memcmp(trns_type, temp.type_, 4) == 0){
            if(plte == nullptr){
                std::cout << "Wrong tRNS!" << std::endl;
                exit(-1);
            }
            for(int32_t i = 0;i != temp.length_; ++i){
                plte[i].w_ = (uint8_t)temp.data_[i] / 255.0f;
            }
        }
    }

// Inflate The IDATs
// TODO: Implement Inflate zlib method.
    int32_t idat_size = 0;
    for(auto chunk : idats)
        idat_size += chunk->length_;
    char *input = new char[idat_size];

    int32_t index = 0;
    for(auto chunk : idats){  
        std::memcpy(&input[index], chunk->data_, chunk->length_);
        index += chunk->length_;
        delete chunk;
    }

    std::vector<char> output;
    output.resize(1000);

    z_stream infstream;
    while(true){
        infstream.zalloc = Z_NULL;
        infstream.zfree = Z_NULL;
        infstream.opaque = Z_NULL;
        infstream.avail_in = idat_size;
        infstream.next_in = (Byte*)input;
        infstream.avail_out = output.size();
        infstream.next_out = (Byte*)&output[0];
        inflateInit(&infstream);
        int32_t ret = inflate(&infstream, Z_NO_FLUSH);
        inflateEnd(&infstream);
        if(ret != Z_STREAM_END){
            output.resize(output.size() + 1000);
            continue;
        }
        break;
    }
    output.resize(infstream.total_out);
    delete[] input;
//debug------------
    std::cout << "inflate size: " << output.size() << std::endl;
//debug------------

//Filter the output data:
    int8_t channel = 0;
    if(color_type == 0) channel = 1;
    else if(color_type == 2) channel = 3;
    else if(color_type == 3) channel = 1;
    else if(color_type == 4) channel = 2;
    else if(color_type == 6) channel = 4;

    int32_t bytes_per_row = output.size() / height;
    int32_t bytes_per_pixel = std::max(1, channel * bit_depth / 8);
    char *filtered_data = new char[output.size() - height];

    for(int32_t i = 0;i != height; ++i){
        int32_t filter_type = output[i * bytes_per_row];        
//debug---------
        // if(i > 14) break;
        // std::cout << "filter_type: " << filter_type << std::endl;
//debug---------
        switch(filter_type){
            case 0:
                FilterNone(output, filtered_data, i, bytes_per_row, bytes_per_pixel);
                break;
            case 1:
                FilterSub(output, filtered_data, i, bytes_per_row, bytes_per_pixel);
                break;
            case 2:
                FilterUp(output, filtered_data, i, bytes_per_row, bytes_per_pixel);
                break;
            case 3:
                FilterAverage(output, filtered_data, i, bytes_per_row, bytes_per_pixel);
                break;
            case 4:
                FilterPaeth(output, filtered_data, i, bytes_per_row, bytes_per_pixel);
                break;
            default:
                std::cout << "Wrong Filter Type!: " << filter_type << std::endl;
                exit(-1);
        }
    }
    int32_t filtered_data_size = output.size() - height;
    output.clear();

//Fill the Texture:
    Vector4f *texels = new Vector4f[width * height];
    Texture *texture = new Texture(width, height, texels);

    if(color_type == 0){
        uint32_t max_number = (1 << bit_depth) - 1;
        for(int32_t i = 0;i != width * height; ++i){
            if(bit_depth <= 8){
                int32_t index = i * bit_depth;
                char temp = filtered_data[index / 8];
                uint32_t result = (temp >> (8 - bit_depth - (index % 8))) & Mask8(bit_depth);
                float heft = (float)result / (float)max_number;
                texels[i].x_ = texels[i].y_ = texels[i].z_ = heft;
                texels[i].w_ = 1.0f;
            }else{
                uint32_t result = filtered_data[i * 2];
                result <<= 8;
                result += filtered_data[i * 2 + 1];
                float heft = (float)result / (float)max_number;
                texels[i].x_ = texels[i].y_ = texels[i].z_ = heft;
                texels[i].w_ = 1.0f;
            }
        }
    }else if(color_type == 2){
        int32_t max_number = (1 << bit_depth) - 1;
        if(bit_depth == 8){
            for(int32_t i = 0;i != width * height; ++i){
                uint8_t temp = filtered_data[i * 3];
//debug------
                // if(i / height <= 14){
                //     std::cout << (float)temp << std::endl;
                //     std::cout << std::endl;
                // }
//debug------
                texels[i].x_ = (float)temp / (float)max_number;
                
                temp = filtered_data[i * 3 + 1];
                texels[i].y_ = (float)temp / (float)max_number;

                temp = filtered_data[i * 3 + 2];
                texels[i].z_ = (float)temp / (float)max_number;
                
//debug------
                // if(i / height <= 14){
                //     std::cout << texels[i].x_ << std::endl;
                //     std::cout << texels[i].y_ << std::endl;
                //     std::cout << texels[i].z_ << std::endl;
                //     std::cout << std::endl;
                // }
//debug------

                texels[i].w_ = 1.0f;
            }
        }else if(bit_depth == 16){
            for(int32_t i = 0;i != width * height; ++i){
                uint16_t temp = filtered_data[i * 6];
                temp <<= 8;
                temp += filtered_data[i * 6 + 1];
                texels[i].x_ = (float)temp / (float)max_number;
                
                temp = filtered_data[i * 6 + 2];
                temp <<= 8;
                temp += filtered_data[i * 6 + 3];
                texels[i].y_ = (float)temp / (float)max_number;

                temp = filtered_data[i * 6 + 4];
                temp <<= 8;
                temp += filtered_data[i * 6 + 5];
                texels[i].z_ = (float)temp / (float)max_number;

                texels[i].w_ = 1.0f;
            }
        }
    }else if(color_type == 3){
        for(int32_t i = 0;i != width * height; ++i){
            if(bit_depth <= 8){
                int32_t index = i * bit_depth;
                char temp = filtered_data[index / 8];
                uint32_t result = (temp >> (8 - bit_depth - (index % 8))) & Mask8(bit_depth);
                texels[i] = plte[result];
            }else{
                uint32_t result = filtered_data[i * 2];
                result <<= 8;
                result += filtered_data[i * 2 + 1];
                texels[i] = plte[result];
            }
        }
    }else if(color_type == 4){
        uint32_t max_number = (1 << bit_depth) - 1;
        if(bit_depth == 8){
            for(int32_t i = 0;i != width * height; ++i){
                uint16_t temp = filtered_data[i * 2];
                texels[i].x_ = texels[i].y_ = texels[i].z_ =
                    (float)temp / (float)max_number;

                temp = filtered_data[i * 2 + 1];
                texels[i].w_ = (float)temp / (float)max_number;
            }
        }else{
            for(int32_t i = 0;i != width * height; ++i){
                uint16_t temp = filtered_data[i * 4];
                temp <<= 8;
                temp += filtered_data[i * 4 + 1];
                texels[i].x_ = texels[i].y_ = texels[i].z_ =
                    (float)temp / (float)max_number;

                temp = filtered_data[i * 4 + 2];
                temp <<= 8;
                temp += filtered_data[i * 4 + 3];
                texels[i].w_ = (float)temp / (float)max_number;
            }
        }
    }else if(color_type == 6){
        int32_t max_number = (1 << bit_depth) - 1;
        if(bit_depth == 8){
            for(int32_t i = 0;i != width * height; ++i){
                uint16_t temp = filtered_data[i * 4];
                texels[i].x_ = (float)temp / (float)max_number;
                
                temp = filtered_data[i * 4 + 1];
                texels[i].y_ = (float)temp / (float)max_number;

                temp = filtered_data[i * 4 + 2];
                texels[i].z_ = (float)temp / (float)max_number;
                
                temp = filtered_data[i * 4 + 3];
                texels[i].w_ = (float)temp / (float)max_number;
            }
        }else if(bit_depth == 16){
            for(int32_t i = 0;i != width * height; ++i){
                uint16_t temp = filtered_data[i * 8];
                temp <<= 8;
                temp += filtered_data[i * 8 + 1];
                texels[i].x_ = (float)temp / (float)max_number;
                
                temp = filtered_data[i * 8 + 2];
                temp <<= 8;
                temp += filtered_data[i * 8 + 3];
                texels[i].y_ = (float)temp / (float)max_number;

                temp = filtered_data[i * 8 + 4];
                temp <<= 8;
                temp += filtered_data[i * 8 + 5];
                texels[i].z_ = (float)temp / (float)max_number;

                temp = filtered_data[i * 8 + 6];
                temp <<= 8;
                temp += filtered_data[i * 8 + 7];
                texels[i].w_ = (float)temp / (float)max_number;
            }
        }
    }else{
        std::cout << "Wrong Color Type!" << std::endl;
        exit(-1);
    }

// Resource Collect:
    if(plte != nullptr)
        delete[] plte;
    if(filtered_data != nullptr)
        delete[] filtered_data;
    return texture;
}

bool PngLoader::IsPNG(std::ifstream &file){
    char read_magic_number[8];
    char png_magic_number[] = {
        (char)0x89, 0x50, 0x4e, 0x47, 
        0x0d, 0x0a, 0x1a, 0x0a};
    file.read(read_magic_number, 8);
    if(std::memcmp(png_magic_number, read_magic_number, 8)!= 0)
        return false;
    return true;
}

bool PngLoader::FillChunk(std::ifstream &file, Chunk *chunk){
    char temp[4];
    file.read(temp, 4);
    sablin::MemCopyRev(&chunk->length_, temp, 4);
    if(chunk->length_ == 0) return false;

    file.read((char*)chunk->type_, 4);

    chunk->data_ = new char[chunk->length_];
    file.read(chunk->data_, chunk->length_);

    file.read(temp, 4);
    sablin::MemCopyRev(&chunk->crc_, temp, 4);

    return true;
}

void PngLoader::FilterNone(const std::vector<char> &src, char *dst,
        const int32_t cur_height, const int32_t bytes_per_row, const int32_t bytes_per_pixel){
    for(int32_t i = 1;i != bytes_per_row; ++i){
        dst[cur_height * (bytes_per_row - 1) + i - 1] =
            src[cur_height * bytes_per_row + i];
    }
}

void PngLoader::FilterSub(const std::vector<char> &src, char *dst,
        const int32_t cur_height, const int32_t bytes_per_row, const int32_t bytes_per_pixel){
    for(int32_t i = 1;i != bytes_per_row; ++i){
        if(i < bytes_per_pixel + 1){
            dst[cur_height * (bytes_per_row - 1) + i - 1] =
                src[cur_height * bytes_per_row + i];
        }else{
            uint16_t a = dst[cur_height * (bytes_per_row - 1) + i - 1 - bytes_per_pixel];
            a &= Mask16(8);
            uint16_t s = src[cur_height * bytes_per_row + i];
            s &= Mask16(8);

            dst[cur_height * (bytes_per_row - 1) + i - 1] =
                (a + s) % 256;
        }
    }
}

void PngLoader::FilterUp(const std::vector<char> &src, char *dst,
        const int32_t cur_height, const int32_t bytes_per_row, const int32_t bytes_per_pixel){
    if(cur_height == 0){
        for(int32_t i = 1;i != bytes_per_row; ++i)
            dst[i - 1] = src[i];
    }else{
        for(int32_t i = 1;i != bytes_per_row; ++i){
            uint16_t b = dst[(cur_height - 1) * (bytes_per_row - 1) + i - 1];
            b &= Mask16(8);
            uint16_t s = src[cur_height * bytes_per_row + i];
            s &= Mask16(8);

            dst[cur_height * (bytes_per_row - 1) + i - 1] =
                (b + s) % 256;
        }
    }
}

void PngLoader::FilterAverage(const std::vector<char> &src, char *dst,
        const int32_t cur_height, const int32_t bytes_per_row, const int32_t bytes_per_pixel){
    if(cur_height == 0){
        for(int32_t i = 1;i != bytes_per_row; ++i){
            if(i < bytes_per_pixel + 1){
                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    src[cur_height * bytes_per_row + i];
            }else{
                uint16_t a = dst[cur_height * (bytes_per_row - 1) + i - 1 - bytes_per_pixel];
                a &= Mask16(8);
                a >>= 1;
                uint16_t s = src[cur_height * bytes_per_row + i];
                s &= Mask16(8);

                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    (a + s) % 256;
            }
        }
    }else{
        for(int32_t i = 1;i != bytes_per_row; ++i){
            if(i < bytes_per_pixel + 1){
                uint16_t b = dst[(cur_height - 1) * (bytes_per_row - 1) + i - 1];
                b &= Mask16(8);
                b >>= 1;
                uint16_t s = src[cur_height * bytes_per_row + i];
                s &= Mask16(8);

                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    (b + s) % 256;
            }else{
                uint16_t a = dst[cur_height * (bytes_per_row - 1) + i - 1 - bytes_per_pixel];
                a &= Mask16(8);
                uint16_t b = dst[(cur_height - 1) * (bytes_per_row - 1) + i - 1];
                b &= Mask16(8);
                uint16_t s = src[cur_height * bytes_per_row + i];

                uint16_t value = (a + b) >> 1;
                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    (value + s) % 256;
            }
        }
    }
}

void PngLoader::FilterPaeth(const std::vector<char> &src, char *dst,
        const int32_t cur_height, const int32_t bytes_per_row, const int32_t bytes_per_pixel){
    if(cur_height == 0){
        for(int32_t i = 1;i != bytes_per_row; ++i){
            if(i < bytes_per_pixel + 1){
                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    src[cur_height * bytes_per_row + i];
            }else{
                uint16_t a = dst[cur_height * (bytes_per_row - 1) + i - 1 - bytes_per_pixel];
                a &= Mask16(8);
                uint16_t s = src[cur_height * bytes_per_row + i];
                s &= Mask16(8);

                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    (a + s) % 256;
            }
        }
    }else{
        for(int32_t i = 1;i != bytes_per_row; ++i){
            if(i < bytes_per_pixel + 1){
                uint16_t b = dst[(cur_height - 1) * (bytes_per_row - 1) + i - 1];
                b &= Mask16(8);
                uint16_t s = src[cur_height * bytes_per_row + i];
                s &= Mask16(8);

                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    (b + s) % 256;
            }else{
                int16_t a = dst[cur_height * (bytes_per_row - 1) + i - 1 - bytes_per_pixel];
                a &= Mask16(8);
                int16_t b = dst[(cur_height - 1) * (bytes_per_row - 1) + i - 1];
                b &= Mask16(8);
                int16_t c = dst[(cur_height - 1) * (bytes_per_row - 1) + i - 1 - bytes_per_pixel];
                c &= Mask16(8);
                int16_t s = src[cur_height * bytes_per_row + i];
                s &= Mask16(8);

                int16_t p = a + b - c;
                int16_t pa = std::abs(p - a);
                int16_t pb = std::abs(p - b);
                int16_t pc = std::abs(p - c);
                int16_t pr;

                if(pa <= pb && pa <= pc) 
                    pr = a;
                else if(pb <= pc)
                    pr = b;
                else
                    pr = c;

                dst[cur_height * (bytes_per_row - 1) + i - 1] =
                    (pr + s) % 256;
            }
        }
    }
}

}
