#pragma once

#include <string>
#include "File.h"
#include "Vec2.h"

static class Settings
{
public:
    Settings();

    static bool get_config();
    static void update_config();

    static bool fullscreen();
    static int width();
    static int height();

    static Vec2 entity_size();
    static float tex_size();
    static float player_size();

    static std::string settings_file_name();

private:
    static bool m_fullscreen;
    static bool m_mode_found;

    static int m_width, m_height;

    static float m_entity_sizew;
    static float m_entity_sizeh;
    static float m_tex_size;
    static float m_player_size;
} s;
