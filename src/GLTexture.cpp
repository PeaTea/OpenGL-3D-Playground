#include "GLTexture.h"
#include <stb_image.h>
#include <iostream>
#include "OutUtils.h"

#define STB_IMAGE_IMPLEMENTATION

GLTexture::GLTexture()
    :   texture_id  {0}
{
}

GLTexture::GLTexture(const std::string& filename, GLTexFlags wrap_s, GLTexFlags wrap_t, GLTexFlags min_filter,
                     GLTexFlags mag_filter, bool prefix)
{
    create_texture(filename, wrap_s, wrap_t, min_filter, mag_filter, prefix);
}

void GLTexture::create_texture(const std::string& filename, GLTexFlags wrap_s, GLTexFlags wrap_t,
                               GLTexFlags min_filter, GLTexFlags mag_filter, bool prefix)
{
    if(filename != "NONE")
    {
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        int w, h, channels;

        std::string path = prefix ? "Data/Textures/" + filename : filename;

        unsigned char* image = stbi_load(path.c_str(), &w, &h, &channels, STBI_rgb_alpha);
        if(image == nullptr)
        {
            output::print(stbi_failure_reason);
            logging::log("Could not load file: ", lstream::error);
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
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
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

        if(glewIsSupported("GL_EXT_texture_filter_anisotropic"))
        {
            glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropic_filtering);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropic_filtering);
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
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    for(int i = 0; i < filenames.size(); i++)
    {
        int w, h, channels;
        unsigned char* image = stbi_load(filenames[i].c_str(), &w, &h, &channels, STBI_rgb_alpha);

        if(image == nullptr)
        {
            output::print(stbi_failure_reason);
            logging::log("Could not load file: " + filenames[i], lstream::error);
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
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
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
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
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
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
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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