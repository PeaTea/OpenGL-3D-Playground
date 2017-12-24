#pragma once

#include <glm/glm.hpp>
#include "GLShader.h"

class BasicLight
{
public:
    BasicLight(const glm::vec3& obj_color, const glm::vec3& light_color,
               const GLShader& light_vs, const GLShader& light_fs);
    ~BasicLight();

private:
    glm::vec3 ObjColor;
    glm::vec3 LightColor;
};

