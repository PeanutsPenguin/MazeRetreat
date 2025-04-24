#include "Resources/Shader.h"
#include <fstream>
#include <iostream>

std::string Resources::Shader::ReadShader(const char* filename)
{
	std::ifstream f(filename);
	std::string buff;
	if (f) 
	{
		std::ostringstream ss;
		ss << f.rdbuf(); 
		buff = ss.str();
	}
	return buff;
}

unsigned int Resources::Shader::SetShader(const char* filename, GLenum mode)
{
	std::string shader = ReadShader(filename);
	const char* source = shader.c_str();
	
	unsigned int shader_id = glCreateShader(mode);
	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);
	
	int success; 
	char infoLog[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
	    glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	    return -1;
	}
	
	return shader_id;
}