#ifndef GLSHADER_H
#define GLSHADER_H

#include "File.h"
#include "Shaderfile.h"

#include <GL/glew.h>

enum Shadertype
{
    VERTEX = 0,
    FRAGMENT = 1,
    GEOMETRY = 2
};

class GLShader
{
public:
    GLShader(File file, Shadertype type);
    GLShader(conststrref data, Shadertype type);

    ~GLShader();

    GLuint id();
    void destroy();

private:
    void check_for_errors();

    GLuint shader_id;
};

#endif