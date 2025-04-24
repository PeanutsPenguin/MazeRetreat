#pragma once

#include "Resources/Scene.h"
#include "LowRenderer/camera.h"
#include "pch.h"

namespace Collision
{
	float RaytoAAB(Resources::SceneNode* object, Visual::Camera* Ray);

	int getMax(int one, int two);

	int getMin(int one, int two);

	LibMath::Vec3 getObjectMin(Resources::SceneNode* object, Visual::Camera* camera);

	LibMath::Vec3 getObjectMax(Resources::SceneNode* object, Visual::Camera* camera);

	LibMath::Vec4 convertCoord(LibMath::Vec4 Position, LibMath::Mat4 transform);
}



