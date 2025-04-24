#pragma once
#include "Resources/ResourceManager.h"

namespace Resources
{
	template<typename _Type>
	_Type* ResourcesManager::CreateRessource(std::string name)
	{	
		this->DeleteResource(name);

		_Type* _data = DBG_NEW _Type(name);
		
		this->_resources[name] = _data;

		return _data;
	}

	template<typename _Type>
	_Type* ResourcesManager::GetRessource(std::string name)
	{
		return this->_resources.at(name);
	}
}
