#pragma once
#include "Scene.h"

namespace Resources
{
	template<typename _Type>
	Scene& Resources::Scene::insert(const _Type& toInsert)
	{
		this->nodes.push_back(DBG_NEW _Type(toInsert));
		return *this;
	}
}
