#pragma once

#include <string>
#include "File.h"

class Settings
{
public:
    Settings() = delete;

    static void get_config();
    static void update_config();

    static bool fullscreen();
    static int width();
    static int height();

    static std::string settings_file_name();

private:
    static bool m_fullscreen;
    static int m_width, m_height;

    static bool is_initialized;
};
