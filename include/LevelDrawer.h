#pragma once

#include <vector>
#include "GLTexture.h"
#include "Level.h"

struct LevelDrawer
{
    static void render(std::vector<GLTexture>& textures, const Level& lvl);
};