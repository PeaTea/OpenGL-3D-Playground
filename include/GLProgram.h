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

    void auto_gen(const shaderfile::Data& shader_sources);

    void set_int	(const GLchar* varname, const GLint& i);
    void set_float	(const GLchar* varname, const GLfloat& f);

    void set_vec2	(const GLchar* varname, const glm::vec2& v2);
    void set_vec3	(const GLchar* varname, const glm::vec3& v3);
    void set_vec4	(const GLchar* varname, const glm::vec4& v4);
    void set_mat4	(const GLchar* varname, const glm::mat4& m4);

private:
    void check_for_errors();

    GLuint program_id;
};

#endif