#include "Settings.h"
#include "Logging.h"

#include <vector>
#include <sstream>
#include <iterator>
#include <cctype>
#include <algorithm>

#define SETTINGS_FILE_NAME "Data/settings.cfg"

bool Settings::m_fullscreen = false;
bool Settings::is_initialized = false;
int Settings::m_width = 0;
int Settings::m_height = 0;

void Settings::get_config()
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

        std::transform(words[2].begin(), words[2].end(), words[2].begin(), ::tolower);

        if(words[0] == "Fullscreen")
        {
            m_fullscreen = (words[2] == "true") ? true : false;
        } 
        else if(words[0] == "Width")
        {
            m_width = std::stoi(words[2]);
        }
        else if(words[0] == "Height")
        {
            m_height = std::stoi(words[2]);
        }
        else
        {
            logging::log("Unrecognized setting: " + words[0], lstream::warning);
        }
    }

    is_initialized = true;
}

void Settings::update_config()
{

}


bool Settings::fullscreen()
{
    if(!is_initialized)
        get_config();

    return m_fullscreen;
}

int Settings::width()
{
    if(!is_initialized)
        get_config();

    if(m_width != 0)
        return m_width;
    else
        logging::log("Invalid value for m_width or settings file not found (width == 0)", lstream::error);
}

int Settings::height()
{
    if(!is_initialized)
        get_config();

    if(m_height != 0)
        return m_height;
    else
        logging::log("Invalid value for m_height or settings file not found (height == 0)", lstream::error);
}

std::string settings_file_name()
{
    return SETTINGS_FILE_NAME;
}