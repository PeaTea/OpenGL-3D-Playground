#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>
#include <string>
#include <array>

enum GLTexFlags
{
    LINEAR,
    NEAREST,
    REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    CLAMP,
    MIRRORED_REPEAT,
    MIRROR_CLAMP_TO_EDGE
};

class GLTexture
{
public:
    GLTexture();

    GLTexture(const std::string& filename, GLTexFlags wrap_s = REPEAT, GLTexFlags wrap_t = REPEAT,
              GLTexFlags min_filter = LINEAR, GLTexFlags mag_filter = LINEAR, bool prefix = true);

    void create_texture(const std::string& filename, GLTexFlags wrap_s = REPEAT, GLTexFlags wrap_t = REPEAT,
                        GLTexFlags min_filter = LINEAR, GLTexFlags mag_filter = LINEAR, bool prefix = true);

    GLuint id() const;

private:
    GLuint texture_id;
    GLfloat anisotropic_filtering;
};

class GLTextureCube
{
public:
    GLTextureCube(std::array<std::string, 6> filenames, GLTexFlags wrap_r = CLAMP_TO_EDGE, GLTexFlags wrap_s = CLAMP_TO_EDGE, GLTexFlags wrap_t = CLAMP_TO_EDGE,
                  GLTexFlags min_filter = LINEAR, GLTexFlags mag_filter = LINEAR);

    GLTextureCube();

    ~GLTextureCube();

    void gen_cube_map(std::array<std::string, 6> filenames, GLTexFlags wrap_r = CLAMP_TO_EDGE, GLTexFlags wrap_s = CLAMP_TO_EDGE, GLTexFlags wrap_t = CLAMP_TO_EDGE,
                      GLTexFlags min_filter = LINEAR, GLTexFlags mag_filter = LINEAR);

    GLuint id() const;

private:
    GLuint m_texture_id;
};

#endif