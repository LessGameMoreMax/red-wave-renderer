#include "Loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
namespace sablin{

std::string Loader::GetParentPath(const std::string &file_path){
    int32_t last_slash = file_path.rfind("/");
    return file_path.substr(0, last_slash + 1);
}

Model* Loader::LoadOBJModel(const std::string &file_path){
//First pass: count the data and complete material pool
    int64_t triangle_pool_size = 0;
    int64_t coord_pool_size = 0;
    int64_t uv_coord_pool_size = 0;
    int16_t material_pool_size = 0;
    Material *material_pool = nullptr;
    std::map<std::string, Material*> string_material_map;

    std::ifstream obj_file;
    obj_file.open(file_path, std::ios::in);
    if(!obj_file.is_open()){
        std::cout << "Fail to open obj file : " << file_path <<
            std::endl;
        exit(-1);
    }

    std::string line;
    while(!obj_file.eof()){
        getline(obj_file, line);
        std::istringstream line_stream(line);
        std::string promt;
        line_stream >> promt;
        if(promt == "mtllib"){
            std::string material_file_name;
            line_stream >> material_file_name;
            string_material_map = 
                Loader::LoadMTLMaterial(Loader::GetParentPath(file_path)
                        .append(material_file_name));
            material_pool = string_material_map.begin()->second;
            material_pool_size = string_material_map.size();
        }
    }

}

std::map<std::string, Material*>
Loader::LoadMTLMaterial(const std::string &file_path){

}

//TODO: Implement a PNG texture loader.
Texture* Loader::LoadPNGTexture(const std::string&){
    return nullptr;
}
}
