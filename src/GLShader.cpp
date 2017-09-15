#include "GLShader.h"
#include <vector>
#include <iostream>

GLShader::GLShader(File file, Shadertype type)
{
	switch(type)
	{
	case Shadertype::VERTEX:
		shader_id = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Shadertype::FRAGMENT:
		shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	std::string temp = file.get_contents();
	const GLchar* source[1] = { temp.c_str() };

	glShaderSource(shader_id, 1, source, nullptr);

	glCompileShader(shader_id);
	check_for_errors();
}

GLuint GLShader::id()
{
	return shader_id;
}

void GLShader::check_for_errors()
{
	int success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int log_size;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);

		std::vector<GLchar> info_log(log_size);
		glGetShaderInfoLog(shader_id, 1024, nullptr, &info_log[0]);

		std::cerr << "Shader failed to compile: " << std::endl;
		for(auto e : info_log)
		{
			std::cerr << e;
		}

		glDeleteShader(shader_id);
	} else return;
}

void GLShader::destroy()
{
	glDeleteShader(this->shader_id);
}