#ifndef COORD_DEF_H
#define COORD_DEF_H

#include <GL/glew.h>
#include "Settings.h"

namespace COORD_DEFS
{
    const float size = 3;

    GLfloat vertices[] =
    {
         0.5f,	0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,	0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f
    };

    GLint indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    GLfloat cube_vertices[] = 
    {
        // Vertices           Normals             TexCoords
         -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, size, 0.0f,
         0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, size, size,
         0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, size, size,
         -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, size,
         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, size, 0.0f,
         0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, size, size,
         0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, size, size,
         -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, size,
         -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

         -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, size, 0.0f,
         -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, size, size,
         -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, size,
         -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, size,
         -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, size, 0.0f,

         0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, size, 0.0f,
         0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, size, size,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, size,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, size,
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, size, 0.0f,

         -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, size,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, size, size,
         0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, size, 0.0f,
         0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, size, 0.0f,
         -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, size,

         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, size,
         0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, size, size,
         0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, size, 0.0f,
         0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, size, 0.0f,
         -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
         -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, size
    };
}


#endif
