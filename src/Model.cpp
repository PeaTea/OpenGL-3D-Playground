#include "Model.h"
#include "ObjRenderer.h"

Model::Model()
{
}

Model::Model(ObjData& data)
{
    create_model(data);
}

void Model::create_model(ObjData& data)
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo_vertices);
    glGenBuffers(1, &m_vbo_normals);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);


    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);

    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(data.vertices[0]), &data.vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_normals);

    glBufferData(GL_ARRAY_BUFFER, data.normals.size() * sizeof(data.normals[0]), &data.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.elements.size() * sizeof(data.elements[0]), &data.elements[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    m_triangle_count = data.elements.size();
}

void Model::render(const glm::vec3& position, const GLuint& texture_id, const Vec2<float>& size)
{
    ObjRenderer::render(*this, texture_id, position, size);
}

GLuint Model::vaoID()
{
    return m_vao;
}

GLuint Model::triangle_count()
{
    return m_triangle_count;
}