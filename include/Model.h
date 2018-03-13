#pragma once

#include "ObjLoader.h"
#include "Vec2.h"

#include <GL/glew.h>

class Model
{
public:
    Model();
    Model(ObjData& data);
    void create_model(ObjData& data);

    void render(const glm::vec3& position, const GLuint& texture_id, const Vec2<float>& size);

    GLuint vaoID();
    GLuint triangle_count();

private:
    GLuint m_vao;
    GLuint m_vbo_vertices;
    GLuint m_vbo_normals;
    GLuint m_ebo;
    GLuint m_triangle_count;
};