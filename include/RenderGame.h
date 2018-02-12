#pragma once

#ifndef RENDERGAME_H
#define RENDERGAME_H

#include "Renderer.h"
#include "GLProgram.h"
#include "Camera.h"
#include "Settings.h"
#include "LevelDrawer.h"
#include "Level.h"
#include "BasicLightSource.h"
#include "Skybox.h"

#include <map>

namespace RG_GB
{
    const float FOV = 110.0f;
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
    GLASS_LIGHT,
    BASIC_CIRCLE,
    SKYBOX
};


class RenderGame
{
public:
    RenderGame(int width, int height, int current_lvl, Camera& camera);

    void render(Camera& camera);
    void render_transparent();

    void update_camera_pos(const glm::vec3& cam_pos);

    void set_deltatime(float dt);

    std::vector<Level> m_levels;
    std::vector<BasicLightSource> m_light_sources;

private:
    void set_uniforms();
    void update_matrices(glm::mat4 view_mat, glm::mat4 projection_mat);

    void load_shaders();
    void load_levels();
    void load_textures();
    void load_entities();
    void load_light_sources();
    void load_objects();

private:
    std::map<std::string, GLProgram> m_programs;

    int m_screen_w;
    int m_screen_h;
    int m_current_lvl;

    float m_deltatime;

    std::vector<GLTexture> m_textures;
    LevelDrawer m_ld;
    GLTextureCube m_skybox_cube_map;
    Skybox m_skybox;

    glm::vec3 m_cam_pos;
};

#endif