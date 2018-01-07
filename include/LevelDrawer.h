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
    
    void render(std::vector<GLTexture>& textures, const Level& lvl, GLProgram& program);

private:
    std::array<PixelData, 6> m_pixeldata;
    bool skip[4];
};