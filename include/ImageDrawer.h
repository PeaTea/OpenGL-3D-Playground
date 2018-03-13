#pragma once

#include <vector>
#include <array>

#include "GLTexture.h"
#include "Level.h"
#include "Types.h"

struct PixelPosition
{
    int i;
    int j;
};

struct PixelData
{
    GLuint texture;
    glm::vec4 color;
    PixelPosition pos;
};

struct ImageDrawer
{
    ImageDrawer();
    
    // Fast performance
    void render_2D(const std::unordered_map<int, GLTexture>& textures, const Level& lvl, GLProgram& program);

    // For complex lightning
    void render_cubes(const std::unordered_map<int, GLTexture>& textures, const Level& lvl, GLProgram& program);

    int get_cf_height() const;

    void set_lvl(Level& lvl);

private:
    std::array<PixelData, 6> m_pixeldata;
    float m_tex_size;
    int m_cf_height;
    bool skip[4];

    float xz_scaling;
    float y_scaling;

    int level_width;
    int level_height;

    float scaled_tex_size_xz;
    float scaled_tex_size_y;

    std::vector<sf::Color> level_pixel_colors;
};