#include "Shaderfile.h"

#include "GLShader.h"

namespace shaderfile
{
    Data parse(conststrref path)
    {
        File shader_file{path};
        std::vector<std::string> lines = shader_file.read_lines();

        uint current = VERTEX;

        Data result;
        for(const auto& line : lines)
        {
            if(line == "!shadertype::vertex")
                current = VERTEX;
            else if(line == "!shadertype::fragment")
                current = FRAGMENT;
            else if(line == "!shadertype::geometry")
                current = GEOMETRY;
            else
                result.data[current] += (line + "\n");
        }

        return result;
    }
}
