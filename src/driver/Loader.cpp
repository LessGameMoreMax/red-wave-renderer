#include "Loader.h"
#include "../data/ModelPool.h"
#include <fstream>
#include <sstream>
#include <iostream>
namespace sablin{

std::string Loader::GetParentPath(const std::string &file_path){
    int32_t last_slash = file_path.rfind("/");
    return file_path.substr(0, last_slash + 1);
}

int8_t Loader::JudgeTriangleNumber(const std::string &points){
    int8_t point_number = 0;
    std::istringstream string_stream(points);
    std::string temp;
    while(!string_stream.eof()){
        string_stream >> temp;
        ++point_number;
    }
    if(point_number == 3)
        return 1;
    if(point_number == 4)
        return 2;
    std::cout << "f point number beyond 4!" << std::endl;
    exit(-1);
}

Vector2f* Loader::ParseUVCoord(const std::string& heft, Mesh *mesh){
    int16_t first_slash = heft.find('/');
    int16_t second_slash = heft.rfind('/');
    if(first_slash + 1 == second_slash ||
            first_slash == heft.size()-1 ||
                first_slash == -1)
        return nullptr;
    if(first_slash == second_slash)
        return &mesh->uv_coord_pool_[
            std::stoi(heft.substr(first_slash + 1, heft.size()))-1];
    return &mesh->uv_coord_pool_[
        std::stoi(heft.substr(first_slash + 1, second_slash))-1];
}

int64_t Loader::ParseVertexCoord(const std::string &heft){
    return std::stoi(heft.substr(0, heft.find('/'))) - 1;
}

Model* Loader::LoadOBJModel(const std::string &file_path){
//First pass: count the data and complete material pool
    int64_t triangle_pool_size = 0;
    int64_t coord_pool_size = 0;
    int64_t uv_coord_pool_size = 0;
    Material *material_pool = nullptr;
    std::map<std::string, Material*> string_material_map;

    std::ifstream obj_first_file;
    obj_first_file.open(file_path, std::ios::in);
    if(!obj_first_file.is_open()){
        std::cout << "Fail to open obj file : " << file_path <<
            std::endl;
        exit(-1);
    }

    std::string line;
    while(!obj_first_file.eof()){
        getline(obj_first_file, line);
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
        }else if(promt == "v"){
            ++coord_pool_size; 
        }else if(promt == "vt"){
            ++uv_coord_pool_size;
        }else if(promt == "f"){
            int8_t point_number = 0;
            std::string temp;
            while(!line_stream.eof()){
                line_stream >> temp;
                ++point_number;
            }
            if(point_number == 3)
                ++triangle_pool_size;
            if(point_number == 4)
                triangle_pool_size += 2;
        }
    }

    obj_first_file.close();

//TODO: Multi Tread Need Lock!
//Create model and join the model pool
    Mesh *mesh = new Mesh(triangle_pool_size,
                          coord_pool_size,
                          uv_coord_pool_size);
    Model *model = new Model(material_pool, mesh);
    ModelPool::GetSingleton()->ManageModel(model);

//Second Pass: Fill the mesh.
    std::ifstream obj_second_file;
    obj_second_file.open(file_path, std::ios::in);
    if(!obj_second_file.is_open()){
        std::cout << "Fail to open second obj file: " <<
            file_path << std::endl;
        exit(-1);
    }

    Material *current_material = nullptr;
    int64_t triangle_pool_index = 0;
    int64_t coord_pool_index = 0;
    int64_t uv_coord_pool_index = 0;
    while(!obj_second_file.eof()){
        getline(obj_second_file, line);
        std::istringstream line_stream(line);
        std::string promt;
        line_stream >> promt;
        if(promt == "v"){
            std::string heft;
            line_stream >> heft;
            mesh->coord_pool_[coord_pool_index]
                .x_ = std::stof(heft);
            line_stream >> heft;
            mesh->coord_pool_[coord_pool_index]
                .y_ = std::stof(heft);
            line_stream >> heft;
            mesh->coord_pool_[coord_pool_index]
                .z_ = std::stof(heft);
            mesh->coord_pool_[coord_pool_index]
                .w_ = 1.0f;
            ++coord_pool_index;
        }else if(promt == "vt"){
            std::string heft;
            line_stream >> heft;
            mesh->uv_coord_pool_[uv_coord_pool_index]
                .x_ = std::stof(heft);
            line_stream >> heft;
            mesh->uv_coord_pool_[uv_coord_pool_index]
                .y_ = std::stof(heft);
            ++uv_coord_pool_index;
        }else if(promt == "usemtl"){
            std::string material_name;
            line_stream >> material_name;
            current_material =
                string_material_map.find(material_name)->second;
        }else if(promt == "f"){
            std::string heft;
            std::vector<std::string> hefts;
            while(!line_stream.eof()){
                line_stream >> heft;
                hefts.push_back(heft);
            }
            
            std::vector<std::vector<std::string>> triangles;
            if(hefts.size() == 4){
                triangles.push_back(std::vector<std::string>{
                            hefts[0], hefts[1], hefts[3]});
                triangles.push_back(std::vector<std::string>{
                            hefts[1], hefts[2], hefts[3]});
            }else{
                triangles.push_back(hefts);
            }
            
            for(auto iter = triangles.begin();
                    iter != triangles.end(); ++iter){
                
                int64_t one_coord = ParseVertexCoord((*iter)[0]);
                Vertex one{
                    &mesh->coord_pool_[one_coord],
                    ParseUVCoord((*iter)[0], mesh)};
                if(mesh->vertex_normal_map_[one_coord] == nullptr){
                    mesh->vertex_normal_map_[one_coord]
                        = &mesh->triangle_pool_[triangle_pool_index]
                            .vertex_a_;
                }
                mesh->triangle_pool_[triangle_pool_index]
                    .vertex_a_ = one;


                int64_t two_coord = ParseVertexCoord((*iter)[1]);
                Vertex two{
                    &mesh->coord_pool_[two_coord],
                    ParseUVCoord((*iter)[1], mesh)};
                if(mesh->vertex_normal_map_[two_coord] == nullptr){
                    mesh->vertex_normal_map_[two_coord]
                        = &mesh->triangle_pool_[triangle_pool_index]
                            .vertex_b_;
                }
                mesh->triangle_pool_[triangle_pool_index]
                    .vertex_b_ = two;

                int64_t three_coord = ParseVertexCoord((*iter)[2]);
                Vertex three{
                    &mesh->coord_pool_[three_coord],
                    ParseUVCoord((*iter)[2], mesh)};
                if(mesh->vertex_normal_map_[three_coord] == nullptr){
                    mesh->vertex_normal_map_[three_coord]
                        = &mesh->triangle_pool_[triangle_pool_index]
                            .vertex_c_;
                }
                mesh->triangle_pool_[triangle_pool_index]
                    .vertex_c_ = three;

                mesh->triangle_pool_[triangle_pool_index]
                    .material_ = current_material;
                mesh->triangle_pool_[triangle_pool_index]
                    .normal_ = Triangle::CalculateTriangleNormal(
                            mesh->triangle_pool_[triangle_pool_index]);
                ++triangle_pool_index;
            }
        }
    }

    obj_second_file.close();
    
    //Build HEdge Structure
    //Calculate Vertex Normal
    return model;
}

std::map<std::string, Material*>
Loader::LoadMTLMaterial(const std::string &file_path){
//first pass: get material number
    int16_t material_pool_size = 0;

    std::ifstream material_first_file;
    material_first_file.open(file_path, std::ios::in);
    if(!material_first_file.is_open()){
        std::cout << "Fail to open first material file : " <<
            file_path << std::endl;
        exit(-1);
    }
    
    std::string line;
    while(!material_first_file.eof()){
        getline(material_first_file, line);
        std::istringstream line_stream(line);
        std::string promt;
        line_stream >> promt;
        if(promt == "newmtl")
            ++material_pool_size;
    }

    material_first_file.close();

//second pass: Construct map and material pool
    std::map<std::string, Material*> string_material_map;
    Material* material_array = new Material[material_pool_size];

    std::ifstream material_second_file;
    material_second_file.open(file_path, std::ios::in);
    if(!material_second_file.is_open()){
        std::cout << "Fail to open second material file : " <<
            file_path << std::endl;
        exit(-1);
    }

    int16_t material_index = -1;
    while(!material_second_file.eof()){
        getline(material_second_file, line);
        std::istringstream line_stream(line);
        std::string promt;
        line_stream >> promt;
        if(promt == "newmtl"){
            ++material_index;
            std::string material_name;
            line_stream >> material_name;
            string_material_map.insert(std::make_pair(material_name,
                        material_array + material_index));
        }else if(promt == "Ns"){
            std::string ns;
            line_stream >> ns;
            material_array[material_index].ns_ = std::stof(ns);
        }else if(promt == "Ni"){
            std::string ni;
            line_stream >> ni;
            material_array[material_index].ni_ = std::stof(ni);
        }else if(promt == "d"){
            std::string d;
            line_stream >> d;
            material_array[material_index].d_ = std::stof(d);
        }else if(promt == "Tr"){
            std::string tr;
            line_stream >> tr;
            material_array[material_index].tr_ = std::stof(tr);
        }else if(promt == "Tf"){
            std::string tf;
            line_stream >> tf;
            material_array[material_index].tf_ = std::stof(tf);
        }else if(promt == "illum"){
            std::string illum;
            line_stream >> illum;
            material_array[material_index].illum_ = std::stoi(illum);
        }else if(promt == "Ka"){
            std::string heft;
            line_stream >> heft;
            material_array[material_index].ka_.x_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].ka_.y_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].ka_.z_ = std::stof(heft);
        }else if(promt == "Kd"){
            std::string heft;
            line_stream >> heft;
            material_array[material_index].kd_.x_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].kd_.y_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].kd_.z_ = std::stof(heft);
        }else if(promt == "Ks"){
            std::string heft;
            line_stream >> heft;
            material_array[material_index].ks_.x_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].ks_.y_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].ks_.z_ = std::stof(heft);
        }else if(promt == "Ke"){
            std::string heft;
            line_stream >> heft;
            material_array[material_index].ke_.x_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].ke_.y_ = std::stof(heft);
            line_stream >> heft;
            material_array[material_index].ke_.z_ = std::stof(heft);
        }else if(promt == "map_Ka"){
            std::string vertex_name;
            line_stream >> vertex_name;
            material_array[material_index].map_ka_ =
                Loader::LoadPNGTexture(Loader::GetParentPath(file_path)
                        .append(vertex_name));
        }else if(promt == "map_Kd"){
            std::string vertex_name;
            line_stream >> vertex_name;
            material_array[material_index].map_kd_ =
                Loader::LoadPNGTexture(Loader::GetParentPath(file_path)
                        .append(vertex_name));
        }
    }

    material_second_file.close();

    if(material_index != material_pool_size - 1){
        std::cout << "material number wrong!" << std::endl;
        delete[] material_array;
        exit(-1);
    }
    return string_material_map;
}

//TODO: Implement a PNG texture loader.
Texture* Loader::LoadPNGTexture(const std::string&){
    return nullptr;
}
}
