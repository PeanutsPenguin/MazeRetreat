#pragma once

#include "LibMath/Vector/Vec3.h"
#include <vector>
#include "pch.h"

namespace Collision
{
	class Box
	{
	public:
		Box() = default;

		Box(const Box&) = default;

		Box(Box&&) = default;

		Box& operator=(const Box&) = default;

		~Box() = default;

		LibMath::Vec3 MaxPos;
		LibMath::Vec3 MinPos;
	};

	bool AABBtoAABB(const Box& objectA, const Box& objectB);

	LibMath::Vec3 getVectorMin(std::vector<LibMath::Vec3> vector);

	LibMath::Vec3 getVectorMax(std::vector<LibMath::Vec3> vector);
}
