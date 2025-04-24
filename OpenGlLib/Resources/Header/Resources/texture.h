#pragma once

///Project Include
#include "Resources/Iresources.h"
#include "pch.h"

///STB Image include
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include "stb_image.h"

///Standart include
#include <string>

namespace Resources
{
	class Texture : public IResources
	{
	public:
		Texture() = default;

		Texture(std::string& filename);

		~Texture() override = default;

		int height = 0;
		int width = 0;
		int channels = 0;
		unsigned char* data;
		unsigned int id = 0;		
		unsigned int index = 0;
	};
}
