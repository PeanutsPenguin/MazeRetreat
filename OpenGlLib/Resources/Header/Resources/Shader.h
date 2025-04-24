#pragma once
#include <iostream>
#include <filesystem>

#include"Resources/Model.h"
#include "pch.h"

namespace Resources
{
	class Shader
	{
	public:
		Shader(void) = default;

		std::string ReadShader(const char* filename);

		unsigned int SetShader(const char* filename, GLenum mode);

		template<typename shader>
		unsigned int Link(std::initializer_list<shader> shaders)
		{
			unsigned int program = glCreateProgram();

			for (shader myshader : shaders)
				glAttachShader(program, myshader);

			glLinkProgram(program);
			
			int success; char infoLog[512];
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
				return -1;
			}

			for (shader myshader : shaders)
				glDeleteShader(myshader);

			return program;
		}

		~Shader(void) = default;

		GLuint SahderProg = 0;
	};

}