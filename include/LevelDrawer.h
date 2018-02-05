#pragma once

#include <vector>
#include <array>
#include "GLTexture.h"
#include "Level.h"

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

struct LevelDrawer
{
    LevelDrawer();
    
    // Fast performance
    void render_2D(std::vector<GLTexture>& textures, const Level& lvl, GLProgram& program);

    // For complex lightning
    void render_cubes(std::vector<GLTexture>& textures, const Level& lvl, GLProgram& program);

    int get_cf_height() const;

private:
    std::array<PixelData, 6> m_pixeldata;
    int m_tex_size;
    int m_cf_height;
    bool skip[4];
};