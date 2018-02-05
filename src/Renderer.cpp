#include "Renderer.h"
#include "Coordinate_Definitions.h"
#include "Logging.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

GLProgram   Renderer::gl_program;
GLuint      Renderer::vao;
GLuint      Renderer::test_cube_vao;
bool        Renderer::enabled_test = false;

Renderer::Renderer()
{
}

Renderer::Renderer(GLProgram program)
{
    gl_program = program;
    init_render_data();
}


void Renderer::init_render_data()
{
    GLuint vbo;
    GLuint ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(COORD_DEFS::vertices), COORD_DEFS::vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(COORD_DEFS::indices), COORD_DEFS::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::set_program(GLProgram program)
{
    if(!gl_program.exists())
    {
        init_render_data();
    } 
    gl_program = program;
}

void Renderer::draw_sprite(GLuint texture_id, glm::vec3 pos, Vec2 size,
                           GLfloat rotation, glm::vec3 rotation_vec, glm::vec4 color)
{
    if(!gl_program.exists())
    {
        logging::log("No program set for Renderer", lstream::error);
    }

    gl_program.use();
    glm::mat4 model;

    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotation), rotation_vec);
    model = glm::scale(model, glm::vec3(size.x, size.y, 1));

    gl_program.set_mat4("model", model);
    gl_program.set_vec4("spritecolor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::draw_sprite_facing_cam(GLuint texture_id, glm::vec3 pos, glm::vec3 cam_pos,
                                      Vec2 size, glm::vec4 color)
{
    if(!gl_program.exists())
    {
        logging::log("No program set for Renderer", lstream::error);
    }

    gl_program.use();
    glm::mat4 model;

    model = glm::translate(model, pos);
    model = glm::rotate(model, atan2(pos.x - cam_pos.x, pos.z - cam_pos.z), {0, 1, 0});
    model = glm::rotate(model, 135.0f, {1, 0, 0});
    model = glm::scale(model, glm::vec3(size.x, size.y, 1));

    gl_program.set_mat4("model", model);
    gl_program.set_vec4("spritecolor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::draw_texture(GLuint texture)
{
    gl_program.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



void Renderer::enable_test()
{
    init_test_render_data();
}

void Renderer::init_test_render_data()
{
    GLuint cube_vbo;

    glGenVertexArrays(1, &test_cube_vao);
    glGenBuffers(1, &cube_vbo);

    glBindVertexArray(test_cube_vao);

    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(COORD_DEFS::cube_vertices), COORD_DEFS::cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)(sizeof(GL_FLOAT) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)(sizeof(GL_FLOAT) * 6));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    enabled_test = true;
}

void Renderer::test_draw_cube(GLuint texture_id, const glm::vec3& pos, const glm::vec3& size, GLfloat rotation, const glm::vec3& rotation_vec,
                              const glm::vec4& color)
{
    if(!enabled_test)
    {
        logging::log("Please enable test first (Renderer::error)", lstream::error);
    }

    gl_program.use();

    glm::mat4 model;

    model = glm::translate(model, pos);
    model = glm::rotate(model, rotation, rotation_vec);
    model = glm::scale(model, size);

    gl_program.set_mat4("model", model);
    gl_program.set_vec4("spritecolor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glBindVertexArray(test_cube_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}