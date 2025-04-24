#pragma once
#include "LibMath/Matrix/Mat4x4.h"

#include "pch.h"

namespace Physics
{
	class Transform 
	{
	public:
		Transform(void);

		Transform(const Transform& toCopy) = default;

		Transform(Transform&& toMove) = default;

		Transform(const LibMath::Mat4& transform) : m_transform(transform) {};

		Transform& translate(const LibMath::Vec3& movement);

		Transform& rotate(const LibMath::Vec3& movement);

		Transform& scale(const LibMath::Vec3& scaling);

		Transform operator* (const Transform& toMutliply) const;

		Transform& operator*=(const Transform& toCheck);

		Transform& operator=(const Transform& toSet) = default;

		bool operator==(const Transform& toCheck) const = default;

		bool operator!=(const Transform& toCheck) const = default;

		~Transform() = default;

		LibMath::Mat4 m_transform;
	};

}