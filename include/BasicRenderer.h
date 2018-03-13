#ifndef RENDERER_H
#define RENDERER_H

#include "GLProgram.h"
#include "GLTexture.h"
#include "Vec2.h"

#include <vector>

class BasicRenderer
{
public:
    BasicRenderer();
    BasicRenderer(GLProgram program);

    static void set_program(GLProgram program);
    static void draw_sprite(const GLuint& texture_id, const glm::vec3& pos, const Vec2<float>& size,
                            const GLfloat& rotation = 180.0f, const glm::vec3& rotation_vec = {1, 0, 0}, const glm::vec4& color = {1, 1, 1, 1});
    static void draw_sprite_facing_cam(const GLuint& texture_id, const glm::vec3& pos, const glm::vec3& cam_pos,
                                       const Vec2<float>& size, const glm::vec4& color = {1, 1, 1, 1});
    static void draw_texture(GLuint texture_id);

    static void enable_cube();
    static void draw_cube(const GLuint& texture_id, const glm::vec3& pos, const glm::vec3& size,
                               const GLfloat& rotation = 0.0f, const glm::vec3& rotation_vec = {1, 0, 0},
                               const glm::vec4& color = {0.5, 0.5, 0.5, 1});

    static void switch_wireframe_mode(const bool& wireframe);

    static glm::mat4 view;
    static glm::mat4 proj;

private:
    static void init_quad_render_data();
    static void init_cube_render_data();

    static GLuint vao;
    static GLuint cube_vao;
    static GLProgram gl_program;
};

#endif