#include "GLTexture.h"
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include "OutUtils.h"


GLTexture::GLTexture(const std::string& filename, GLTexFlags wrap_s, GLTexFlags wrap_t, GLTexFlags min_filter, GLTexFlags mag_filter, bool prefix)
{
    if(filename != "NONE")
    {
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        sf::Image texture;
        if(!texture.loadFromFile(prefix ? "Data/Textures/" + filename : filename))
        {
            std::cerr << "Could not load file: " << filename << std::endl;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
        //glGenerateMipmap(GL_TEXTURE_2D);

        switch(wrap_s)
        {
        case REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            break;
        case CLAMP_TO_EDGE:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            break;
        case CLAMP_TO_BORDER:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            break;
        case CLAMP:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            break;
        case MIRRORED_REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            break;
        case MIRROR_CLAMP_TO_EDGE:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
            break;
        }

        switch(wrap_t)
        {
        case REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case CLAMP_TO_EDGE:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case CLAMP_TO_BORDER:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            break;
        case CLAMP:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
            break;
        case MIRRORED_REPEAT:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        case MIRROR_CLAMP_TO_EDGE:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
            break;
        }

        switch(min_filter)
        {
        case NEAREST:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        case LINEAR:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;
        }

        switch(mag_filter)
        {
        case NEAREST:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case LINEAR:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


GLuint GLTexture::id() const
{
    return texture_id;
}



GLTextureCube::GLTextureCube(std::array<std::string, 6> filenames, GLTexFlags wrap_r, GLTexFlags wrap_s, GLTexFlags wrap_t, GLTexFlags min_filter, GLTexFlags mag_filter)
{
    gen_cube_map(filenames, wrap_s, wrap_t, min_filter, mag_filter);
}

GLTextureCube::GLTextureCube()
{
}

GLTextureCube::~GLTextureCube()
{
    glDeleteTextures(1, &m_texture_id);
}


void GLTextureCube::gen_cube_map(std::array<std::string, 6> filenames, GLTexFlags wrap_r, GLTexFlags wrap_s, GLTexFlags wrap_t, GLTexFlags min_filter, GLTexFlags mag_filter)
{
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    for(int i = 0; i < filenames.size(); i++)
    {
        sf::Image texture;
        if(!texture.loadFromFile(filenames[i]))
        {
            logging::log("Could not load file: " + filenames[i], lstream::error);
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    }

    switch(wrap_r)
    {
    case REPEAT:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
        break;
    case CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        break;
    case CLAMP_TO_BORDER:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
        break;
    case CLAMP:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);
        break;
    case MIRRORED_REPEAT:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
        break;
    case MIRROR_CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_MIRROR_CLAMP_TO_EDGE);
        break;
    }

    switch(wrap_s)
    {
    case REPEAT:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        break;
    case CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        break;
    case CLAMP_TO_BORDER:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        break;
    case CLAMP:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
        break;
    case MIRRORED_REPEAT:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        break;
    case MIRROR_CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
        break;
    }

    switch(wrap_t)
    {
    case REPEAT:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
        break;
    case CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        break;
    case CLAMP_TO_BORDER:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        break;
    case CLAMP:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
        break;
    case MIRRORED_REPEAT:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        break;
    case MIRROR_CLAMP_TO_EDGE:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
        break;
    }

    switch(min_filter)
    {
    case NEAREST:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        break;
    case LINEAR:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        break;
    }

    switch(mag_filter)
    {
    case NEAREST:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        break;
    case LINEAR:
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        break;
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


GLuint GLTextureCube::id() const
{
    return m_texture_id;
}