#include "Resources/ResourceManager.h"

namespace Resources
{
	void ResourcesManager::DeleteResource(std::string name)
	{
		if (this->_resources.contains(name) == true)
		{
			delete this->_resources[name];
			this->_resources.erase(name);
		}
	}

	void ResourcesManager::deleteArray()
	{
		for (auto& resource : ResourcesManager::_resources)
			delete resource.second;

		ResourcesManager::_resources.clear();
	}

	ResourcesManager::~ResourcesManager()
	{
		for (auto& resource : ResourcesManager::_resources)
			delete resource.second;

		ResourcesManager::_resources.clear();
	}
}