#pragma once

#include "Model.h"
#include "GLProgram.h"
#include "Vec2.h"
#include "GLTexture.h"

class ObjRenderer
{
public:
    static void render(Model& m, const GLuint& texture_id, const glm::vec3& position, const Vec2<float>& size);

    static void set_program(GLProgram& prog);

    static void update(const glm::mat4& view, const glm::mat4& proj, const glm::vec3& pos);

private:
    static GLProgram m_program;

    static glm::mat4 view_mat;
    static glm::mat4 proj_mat;
    static glm::vec3 position;
};
