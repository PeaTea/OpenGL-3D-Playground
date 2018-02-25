#pragma once
#include "File.h"
#include "Types.h"

#include <vector>
#include <glm/glm.hpp>

struct ObjData
{
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> normals;
    std::vector<uint> elements;
};

class ObjLoader
{
public:
    ObjLoader();
    ObjLoader(File& file);

    void load_obj_file(File& file);

    ObjData& data();

private:
    ObjData m_data;
    bool found_normals;
};