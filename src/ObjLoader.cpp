#include "ObjLoader.h"
#include "Utils.h"
#include "OutUtils.h"

#include <sstream>


ObjLoader::ObjLoader()
    :   found_normals   {false}
{
}

ObjLoader::ObjLoader(File& file)
    :   found_normals   {false}
{
    load_obj_file(file);
}

void ObjLoader::load_obj_file(File& file)
{
    std::vector<std::string> lines = file.read_lines();
    for(const auto& line : lines)
    {
        std::string identifier {line.substr(0, 2)};
        std::string data = line.substr(2);
        if(identifier == "v ")
        {
            std::istringstream ss{data};
            glm::vec4 v;
            ss >> v.x; ss >> v.y; ss >> v.z; v.w = 1.0f;
            m_data.vertices.push_back(v);
        } else if(identifier == "f ")
        {
            if(data.find("//"))
            {
                std::vector<std::string> values = utils::split(data, '/');
                logging::log("Obj File with included normals not yet supported!", lstream::error);

                found_normals = true;
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
        } else continue;
    }

    if(!found_normals)
    {
        m_data.normals.resize(m_data.vertices.size(), {0, 0, 0});
        for(int i{-1}; i < m_data.elements.size(); )
        {
            uint a = m_data.elements[++i];
            uint b = m_data.elements[++i];
            uint c = m_data.elements[++i];

            glm::vec3 normal = glm::normalize(glm::cross(
                glm::vec3{m_data.vertices[b]} -glm::vec3{m_data.vertices[a]},
                glm::vec3{m_data.vertices[c]} -glm::vec3{m_data.vertices[a]}
            ));
            m_data.normals[a] = m_data.normals[b] = m_data.normals[c] = normal;
        }
    }
}