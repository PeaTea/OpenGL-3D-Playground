#ifndef GLSHADER_H
#define GLSHADER_H

#include "File.h"
#include <GL/glew.h>

enum Shadertype
{
	VERTEX,
	FRAGMENT
};

class GLShader
{
public:
	GLShader(File file, Shadertype type);

	GLuint id();
	void destroy();

private:
	void check_for_errors();

	GLuint shader_id;
};

#endif