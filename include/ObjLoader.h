#pragma once
#include "File.h"
#include "Types.h"

#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

struct ObjData
{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> uvs;
    std::vector<uint> elements;
};

class ObjLoader
{
public:
    void load_obj_file(File& file, ObjData& data);
    void store_obj_file(File& file, conststr name);

    ObjData& data();

    std::unordered_map<std::string, ObjData> objects;

private:
    ObjData m_data;
    bool found_normals;

    std::string tmp_obj_name;
};