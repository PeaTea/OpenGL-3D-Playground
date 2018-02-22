#include "Settings.h"
#include "OutUtils.h"

#include <vector>
#include <sstream>
#include <iterator>
#include <cctype>
#include <algorithm>
#include <iostream>

#define SETTINGS_FILE_NAME "Data/settings.cfg"

const std::string DEFAULTS = "\
# Settings for OpenGL Playground\n\n\
Mode = FULLSCREEN\n\n\
# PC\n\
Fullscreen = false\n\
Width = 800\n\
Height = 600\n\
VSync = true\n\n\
# Sizes\n\
EntitySizeW = 96\n\
EntitySizeH = 128\n\
# Leave at 128 !!!\n\
TexSize = 128\n\
# Should not be much larger than 256\n\
PlayerSize = 128\n\n\
# Debug Settings\n\
ShowFPS = false\n\
";

bool    Settings::m_fullscreen      = false;
bool    Settings::m_mode_found      = false;
bool    Settings::m_show_fps        = false;
bool    Settings::m_enable_vsync    = false;
int     Settings::m_width           = 0;
int     Settings::m_height          = 0;
float   Settings::m_entity_sizew    = 0.0f;
float   Settings::m_entity_sizeh    = 0.0f;
float   Settings::m_tex_size        = 0.0f;
float   Settings::m_player_size     = 0.0f;

Settings::Settings()
{
    get_config();
}

bool Settings::get_config()
{
    File settings_file(SETTINGS_FILE_NAME);
    std::vector<std::string> contents = settings_file.read_lines();
    for(auto& line : contents)
    {
        std::istringstream stream(line);
        std::vector<std::string> words {std::istream_iterator<std::string>(stream),
                                        std::istream_iterator<std::string>()};
        
        if(words.empty())
            continue;

        if(words[0][0] == '#') 
            continue;

        std::transform(words[0].begin(), words[0].end(), words[0].begin(), tolower);
        std::transform(words[2].begin(), words[2].end(), words[2].begin(), tolower);

        if(words[0] == "mode")
        {
            if(words[2] == "fullscreen")
            {
                m_fullscreen = true;
                m_width = 1920;
                m_height = 1080;
            }
            else if(words[2] == "windowed")
            {
                m_fullscreen = false;
                m_width = 800;
                m_height = 600;
            }
            else if(words[2] == "custom")
            {
                continue;
            }
            else
            {
                logging::log("Unrecognized mode: " + words[2], lstream::warning);
                continue;
            }
            m_mode_found = true;
        }
        else if(words[0] == "fullscreen")
        {
            if(!m_mode_found)
                m_fullscreen = (words[2] == "true") ? true : false;
        } 
        else if(words[0] == "width")
        {
            if(!m_mode_found)
                m_width = std::stoi(words[2]);
        }
        else if(words[0] == "height")
        {
            if(!m_mode_found)
                m_height = std::stoi(words[2]);
        }
        else if(words[0] == "entitysizew")
        {
            m_entity_sizew = std::stof(words[2]);
        }
        else if(words[0] == "entitysizeh")
        {
            m_entity_sizeh = std::stof(words[2]);
        }
        else if(words[0] == "playersize")
        {
            m_player_size = std::stof(words[2]);
        }
        else if(words[0] == "texsize")
        {
            m_tex_size = std::stof(words[2]);
        }
        else if(words[0] == "showfps")
        {
            m_show_fps = (words[2] == "true") ? true : false;
        }
        else if(words[0] == "vsync")
        {
            m_enable_vsync = (words[2] == "true") ? true : false;
        }
        else
        {
            logging::log("Unrecognized setting: " + words[0], lstream::warning);
        }
    }

    return true;
}


bool Settings::fullscreen()
{
    return m_fullscreen;
}

bool Settings::show_fps()
{
    return m_show_fps;
}

bool Settings::vsync_enabled()
{
    return m_enable_vsync;
}

int Settings::width()
{
    if(m_width > 0)
        return m_width;
    else
        logging::log("Invalid value for width (width <= 0)", lstream::error);
}

int Settings::height()
{
    if(m_height > 0)
        return m_height;
    else
        logging::log("Invalid value for height (height <= 0)", lstream::error);
}

Vec2<float> Settings::entity_size()
{
    if(m_entity_sizew > 0 && m_entity_sizeh > 0)
        return {m_entity_sizew, m_entity_sizeh};
    else
        logging::log("Invalid or missing value for entity_size (component uninitialized or <= 0)",
                     lstream::error);
}

float Settings::tex_size()
{
    if(m_tex_size > 0)
        return m_tex_size;
    else
        logging::log("Invalid or missing value for TEX_SIZE (<= 0)", lstream::error);
}

float Settings::player_size()
{
    if(m_player_size > 0)
        return m_player_size;
    else
        logging::log("Invalid or missing value for player_size (playersizeh <= 0)",
                     lstream::error);
}

std::string Settings::settings_file_name()
{
    return SETTINGS_FILE_NAME;
}

void Settings::revert_to_defaults()
{
    File settings_file {SETTINGS_FILE_NAME};
    settings_file.write(DEFAULTS);
}