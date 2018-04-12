#include "ObjLoader.h"
#include "Utils.h"
#include "OutUtils.h"

#include <sstream>
#include <algorithm>

void ObjLoader::load_obj_file(File& file, ObjData& data)
{
    m_data.vertices.clear();
    m_data.uvs.clear();
    m_data.elements.clear();
    m_data.normals.clear();

    for(const auto& line : file.read_lines())
    {
        std::string identifier {line.substr(0, 2)};
        std::string numbers = line.substr(2);
        std::istringstream ss{numbers};
        if(identifier == "v ")
        {
            glm::vec3 v;
            ss >> v.x >> v.y >> v.z;
            data.vertices.emplace_back(v);
        }
        else if(identifier == "vt")
        {
            glm::vec3 v;
            ss >> v.x >> v.y >> v.z;
            data.uvs.emplace_back(v);
        }
        else if(identifier == "f ")
        {
            if(numbers.find("/") != std::string::npos)
            {
                found_normals = true;
                std::vector<std::string> values;
                utils::split(numbers, '/', values);
            }
            else
            {
                uint a, b, c;
                ss >> a >> b >> c;
                data.elements.emplace_back(--a);
                data.elements.emplace_back(--b);
                data.elements.emplace_back(--c);
            }
        }
    }

    if(!found_normals)
    {
        data.normals.resize(m_data.vertices.size(), {0, 0, 0});
        for(int i{0}; i < m_data.elements.size(); i += 3)
        {
            uint a = data.elements[i];
            uint b = data.elements[i + 1];
            uint c = data.elements[i + 2];

            glm::vec3 normal = glm::normalize(glm::cross(
                glm::vec3{data.vertices[b]} -glm::vec3{data.vertices[a]},
                glm::vec3{data.vertices[c]} -glm::vec3{data.vertices[a]}
            ));
            data.normals[a] = m_data.normals[b] = m_data.normals[c] = normal;
        }
    }
}

void ObjLoader::store_obj_file(File& file, conststr name)
{
    load_obj_file(file, m_data);
    objects[name] = m_data;
}

ObjData& ObjLoader::data()
{
    return m_data;
}