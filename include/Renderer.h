#ifndef RENDERER_H
#define RENDERER_H

#include "GLProgram.h"
#include <vector>
#include "GLTexture.h"

class Renderer
{
public:
    Renderer();
    Renderer(GLProgram program);

    static void set_program(GLProgram program);
    static void draw_sprite(GLuint texture_id, glm::vec3 pos, glm::vec2 size, GLfloat rotation, glm::vec3 rotation_vec = glm::vec3(0, 0, 1), glm::vec4 color = glm::vec4(1, 1, 1, 1));
    static void draw_texture(GLuint texture_id);

private:
    static void init_render_data();

    static GLuint vao;
    static GLProgram gl_program;
};

#endif