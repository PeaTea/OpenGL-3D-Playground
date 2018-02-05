#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>
#include <string>

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
    GLTexture(const std::string& filename, GLTexFlags wrap_s = REPEAT, GLTexFlags wrap_t = REPEAT,
              GLTexFlags min_filter = LINEAR, GLTexFlags mag_filter = LINEAR, bool prefix = true);

    GLuint id() const;

private:
    GLuint texture_id;

};

#endif