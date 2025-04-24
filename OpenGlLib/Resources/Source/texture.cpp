#include "Resources/texture.h"
#include <string>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Resources
{
	Texture::Texture(std::string& filename)
	{
		///Actvie the texture for Multi Texturing
		glActiveTexture(this->index);
		///Set the if
		glGenTextures(1, &this->id);
		///Bind the texture
		glBindTexture(GL_TEXTURE_3D, this->id);

		///Parameter set to Repeat the color
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		///Load the image with the pathFile given
		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		this->data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
		if (this->data)
		{
			glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, width, height, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);

			glGenerateMipmap(GL_TEXTURE_3D);
		}
		else
			std::cout << "FAILED TO LOAD IMAGE" << std::endl;

		///free the image
		stbi_image_free(this->data);
	}
}

