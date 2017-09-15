#include "GLProgram.h"
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

GLProgram::GLProgram()
{
	program_id = 0;
}

void GLProgram::create()
{
	program_id = glCreateProgram();
}

void GLProgram::attach_shader(GLShader shader)
{
	glAttachShader(program_id, shader.id());
	shader.destroy();
}

void GLProgram::link()
{
	glLinkProgram(program_id);
	check_for_errors();
}

void GLProgram::check_for_errors()
{
	int success;
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		int log_size;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);

		std::vector<GLchar> info_log(log_size);
		glGetProgramInfoLog(program_id, 1024, nullptr, &info_log[0]);

		std::cerr << "Shaderprogram failed to link: \n" << std::endl;
		for(auto e : info_log)
		{
			std::cerr << e;
		}

		glDeleteProgram(program_id);
	} else return;
}

void GLProgram::use()
{
	if(this->exists())	glUseProgram(program_id);
	else throw std::logic_error("Program has not been created!");
}

void GLProgram::unuse()
{
	glUseProgram(0);
}

void GLProgram::set_int(const GLchar* varname, GLint i)
{
	glUniform1i(glGetUniformLocation(program_id, varname), i);
}

void GLProgram::set_float(const GLchar* varname, GLfloat f)
{
	glUniform1f(glGetUniformLocation(program_id, varname), f);
}

void GLProgram::set_vec2(const GLchar* varname, glm::vec2 v2)
{
	glUniform2f(glGetUniformLocation(program_id, varname), v2.x, v2.y);
}

void GLProgram::set_vec3(const GLchar* varname, glm::vec3 v3)
{
	glUniform3f(glGetUniformLocation(program_id, varname), v3.x, v3.y, v3.z);
}

void GLProgram::set_vec4(const GLchar* varname, glm::vec4 v4)
{
	glUniform4f(glGetUniformLocation(program_id, varname), v4.x, v4.y, v4.z, v4.w);
}

void GLProgram::set_mat4(const GLchar* varname, glm::mat4 m4)
{
	glUniformMatrix4fv(glGetUniformLocation(program_id, varname), 1, GL_FALSE, glm::value_ptr(m4));
}

bool GLProgram::exists()
{
	return (program_id == 0) ? false : true;
}
