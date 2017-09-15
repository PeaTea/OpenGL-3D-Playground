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
	GLTexture(const std::string& filename, GLTexFlags wrap_s, GLTexFlags wrap_t, GLTexFlags min_filter, GLTexFlags mag_filter);

	GLuint id();

private:
	GLuint texture_id;

};

#endif