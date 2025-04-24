#pragma once
#include <vector>
#include "pch.h"

namespace DataStructure
{
	///Class for the Graph object 
	template<typename _Type>
	class Graph
	{
	public:
		Graph(void) = default;

		virtual ~Graph(void) = default;

		std::vector<_Type*> nodes;
	};
}