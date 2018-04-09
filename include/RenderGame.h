#pragma once

#ifndef RENDERGAME_H
#define RENDERGAME_H

#include "BasicRenderer.h"
#include "GLProgram.h"
#include "Camera.h"
#include "Settings.h"
#include "ImageDrawer.h"
#include "Image.h"
#include "BasicLightSource.h"
#include "Skybox.h"
#include "FontRenderer.h"
#include "Model.h"

#include <unordered_map>

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
    SUN,
    SKYBOX
};


class RenderGame
{
public:
    RenderGame(const uint& width, const uint& height, const int& current_lvl, Camera& camera);

    void render(Camera& camera, const bool& draw_normals);
    void render_transparent(const bool& draw_fps, const int& fps, const glm::vec3& pos);
    void render_fps(const int& fps, const glm::vec3& pos);

    void update_camera_pos(const glm::vec3& cam_pos);

    void set_deltatime(float dt);

    glm::vec3 get_cam_pos();

    std::vector<Image> m_levels;
    std::vector<BasicLightSource> m_light_sources;

private:
    void update(const glm::mat4& view_mat, const glm::mat4& projection_mat, const glm::vec3& cam_pos);

    void load_shaders();
    void load_levels();
    void load_textures();
    void load_entities();
    void load_light_sources();
    void load_objects();

private:
    std::unordered_map<std::string, GLProgram> m_programs;
    std::unordered_map<std::string, Model> m_models;

    uint m_screen_w;
    uint m_screen_h;
    int m_current_lvl;

    float m_deltatime;

    std::unordered_map<int, GLTexture> m_textures;
    ImageDrawer m_image_drawer;
    FontRenderer font_renderer;
    ObjLoader obj_loader;
    GLTextureCube m_skybox_cube_map;
    Skybox m_skybox;

    glm::vec3 m_cam_pos;
};

#endif