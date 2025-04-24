#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "pch.h"
#include "Resources/Iresources.h"

namespace Resources
{
	class ResourcesManager
	{
	public:
		ResourcesManager(void) = default;

		template <typename _Type>	
		_Type* CreateRessource(std::string name);

		template <typename _Type>
		_Type* GetRessource(std::string name);

		void DeleteResource(std::string name);

		void deleteArray();

		~ResourcesManager();

	private:
		std::unordered_map<std::string, IResources*> _resources;
	};
}

#include "ResourcesManager.hpp"