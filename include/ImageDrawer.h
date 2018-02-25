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

private:
    std::array<PixelData, 6> m_pixeldata;
    float m_tex_size;
    int m_cf_height;
    bool skip[4];
};