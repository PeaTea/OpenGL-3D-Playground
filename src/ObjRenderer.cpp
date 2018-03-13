#include "ObjRenderer.h"
#include <glm/gtc/matrix_transform.hpp>


GLProgram   ObjRenderer::m_program;
glm::mat4   ObjRenderer::view_mat;
glm::mat4   ObjRenderer::proj_mat;
glm::vec3   ObjRenderer::position;

void ObjRenderer::set_program(GLProgram& prog)
{
    m_program = prog;
}

void ObjRenderer::update(const glm::mat4& view, const glm::mat4& proj, const glm::vec3& pos)
{
    view_mat = view;
    proj_mat = proj;
    position = pos;
}

void ObjRenderer::render(Model& m, const GLuint& texture_id, const glm::vec3& position, const Vec2<float>& size)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    m_program.use();

    glm::mat4 model_mat;
    model_mat = glm::translate(model_mat, position);
    model_mat = glm::scale(model_mat, {size.x, size.y, size.x});

    glm::mat4 mvp = proj_mat * view_mat * model_mat;
    m_program.set_mat4("mvp", mvp);
    m_program.set_vec3("view_pos", position);
    m_program.set_mat4("model", model_mat);
    m_program.set_mat4("view", view_mat);
    m_program.set_mat4("projection", proj_mat);

    glBindVertexArray(m.vaoID());

    glDrawElements(GL_TRIANGLES, m.triangle_count(), GL_UNSIGNED_INT, 0);
}
