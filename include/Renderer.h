#ifndef RENDERER_H
#define RENDERER_H

#include "GLProgram.h"
#include "GLTexture.h"
#include "Vec2.h"

#include <vector>

class Renderer
{
public:
    Renderer();
    Renderer(GLProgram program);

    static void set_program(GLProgram program);
    static void draw_sprite(GLuint texture_id, glm::vec3 pos, Vec2 size,
                            GLfloat rotation = 180.0f, glm::vec3 rotation_vec = {1, 0, 0},
                            glm::vec4 color = {1, 1, 1, 1});
    static void draw_sprite_facing_cam(GLuint texture_id, glm::vec3 pos, glm::vec3 cam_pos,
                                       Vec2 size, glm::vec4 color = {1, 1, 1, 1});
    static void draw_texture(GLuint texture_id);

private:
    static void init_render_data();

    static GLuint vao;
    static GLProgram gl_program;
};

#endif