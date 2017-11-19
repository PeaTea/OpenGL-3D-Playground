#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <glm/glm.hpp>
#include "GLShader.h"

class GLProgram
{
public:
    GLProgram();

    void create();
    void attach_shader(GLShader shader);
    void link();
    void use();
    void unuse();
    bool exists();

    void set_int	(const GLchar* varname, GLint i);
    void set_float	(const GLchar* varname, GLfloat f);

    void set_vec2	(const GLchar* varname, glm::vec2 v2);
    void set_vec3	(const GLchar* varname, glm::vec3 v3);
    void set_vec4	(const GLchar* varname, glm::vec4 v4);
    void set_mat4	(const GLchar* varname, glm::mat4 m4);

private:
    void check_for_errors();

    GLuint program_id;
};

#endif