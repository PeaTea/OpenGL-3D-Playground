#include "ObjLoader.h"
#include "Utils.h"
#include "OutUtils.h"

#include <sstream>
#include <algorithm>

void ObjLoader::load_obj_file(File& file)
{
    m_data.vertices.clear();
    m_data.uvs.clear();
    m_data.elements.clear();
    m_data.normals.clear();

    std::vector<std::string> lines = file.read_lines();
    for(const auto& line : lines)
    {
        std::string identifier {line.substr(0, 2)};
        std::string data = line.substr(2);
        if(identifier == "v ")
        {
            std::istringstream ss{data};
            glm::vec3 v;
            ss >> v.x; ss >> v.y; ss >> v.z;
            m_data.vertices.push_back(v);
        }
        else if(identifier == "vt")
        {
            std::istringstream ss{data};
            glm::vec3 v;
            ss >> v.x; ss >> v.y; ss >> v.z;
            m_data.uvs.push_back(v);
        }
        else if(identifier == "f ")
        {
            if(data.find("/") != std::string::npos)
            {
                logging::log("Obj File with included normals not yet supported!", lstream::exception);

                found_normals = true;
                std::vector<std::string> values = utils::split(data, '/');
            }
            else
            {
                std::istringstream ss{data};
                uint a, b, c;
                ss >> a; ss >> b; ss >> c;
                --a; --b; --c;
                m_data.elements.push_back(a);
                m_data.elements.push_back(b);
                m_data.elements.push_back(c);
            }
        } 
        else continue;
    }

    if(!found_normals)
    {
        m_data.normals.resize(m_data.vertices.size(), {0, 0, 0});
        for(int i{0}; i < m_data.elements.size(); i += 3)
        {
            uint a = m_data.elements[i];
            uint b = m_data.elements[i + 1];
            uint c = m_data.elements[i + 2];

            glm::vec3 normal = glm::normalize(glm::cross(
                glm::vec3{m_data.vertices[b]} -glm::vec3{m_data.vertices[a]},
                glm::vec3{m_data.vertices[c]} -glm::vec3{m_data.vertices[a]}
            ));
            m_data.normals[a] = m_data.normals[b] = m_data.normals[c] = normal;
        }
    }
}

void ObjLoader::store_obj_file(File& file, conststr name)
{
    load_obj_file(file);
    objects[name] = m_data;
}

ObjData& ObjLoader::data()
{
    return m_data;
}