#ifndef RENDERGAME_H
#define RENDERGAME_H

#include "Renderer.h"
#include "GLProgram.h"
#include "Camera.h"
#include "Level.h"

namespace RG_GB
{
    const float FOV = 110.0f;
    const glm::vec2 TEX_SIZE(128, 128);
}

enum Textures
{
    METAL_CUBE,
    ACID,
    STONE,
    LAVA,
    MARBLE,
    WOOD,
    QUAD_TEMPLATE,
    DIAGONAL_TEMPLATE,
    MYSTERIOUS_ROBOT,
    TRANSPARENCY_TEST,
};

class RenderGame
{
public:
    RenderGame(int width, int height);

    void render(Camera& camera);
    void render_transparent();

    std::vector<Level> levels;

private:
    void load_textures();
    void set_uniforms();
    void update_matrices(glm::mat4 view_mat, glm::mat4 projection_mat);

    void load_levels();

    GLProgram gl_program;

    int screen_w;
    int screen_h;

    std::vector<GLTexture> textures;

    //Game Objects
};

#endif