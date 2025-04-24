#include "Physics/Collision.h"

namespace Collision
{
	float RaytoAAB(Resources::SceneNode* object, Visual::Camera* Ray)
	{
		LibMath::Vec3 minObject = getObjectMin(object, Ray);
		LibMath::Vec3 maxObject = getObjectMax(object, Ray);

		float minX = 0;
		if (Ray->Front.x != 0)
			minX = (minObject.x - Ray->Position.x) / Ray->Front.x;
		else
			minX = (minObject.x -  Ray->Position.x);

		float minY = 0;
		if (Ray->Front.y != 0)
			minY = (minObject.y -  Ray->Position.y) / Ray->Front.y;
		else
			minY = (minObject.x -  Ray->Position.y);
	
		float minZ = 0;
		if (Ray->Front.z != 0)
			minZ = (minObject.z -  Ray->Position.z) / Ray->Front.z;
		else
			minZ = (minObject.z -  Ray->Position.z);

		float maxX = 0;
		if (Ray->Front.x != 0)
			maxX = (maxObject.x -  Ray->Position.x) / Ray->Front.x;
		else
			maxX = (maxObject.x -  Ray->Position.x);

		float maxY = 0;
		if (Ray->Front.y != 0)
			maxY = (maxObject.y -  Ray->Position.y) / Ray->Front.y;
		else
			maxY = (maxObject.y -  Ray->Position.y);

		float maxZ = 0;
		if (Ray->Front.z != 0)
			maxZ = (maxObject.z -  Ray->Position.z) / Ray->Front.z;
		else
			maxZ = (maxObject.z -  Ray->Position.z);

		float MinCoord = getMax(getMax(getMin(minX, maxX), getMin(minY, maxY)), getMin(minZ, maxZ));

		float MaxCoord = getMin(getMin(getMax(minX, maxX), getMax(minY, maxY)), getMax(minZ, maxZ));

		if (MaxCoord < 0)
			return -1;
		else if (MinCoord > MaxCoord)
			return -1;
		else if (MinCoord < 0)
			return MaxCoord;
		else
			return MinCoord;
	}

	int getMax(int one, int two)
	{
		return one < two ? two : one;
	}

	int getMin(int one, int two)
	{
		return one < two ? one : two;
	}

	LibMath::Vec3 getObjectMin(Resources::SceneNode* object, Visual::Camera* camera)
	{
		LibMath::Vec3 result;

		for(int i = 0; i < object->getModel()->vertexBuffer.size(); ++i)
		{
			LibMath::Vec4 check = convertCoord(LibMath::Vec4(object->getModel()->vertexBuffer[i].position), object->local.m_transform);
			
			if(i == 0)
			{ 
				result = check;
			}
			
			if (check.x < result.x)
				result.x = check.x;

			if (check.y < result.y)
				result.y = check.y;

			if (check.z < result.z)
				result.z = check.z;
		}

		return result;
	}

	LibMath::Vec3 getObjectMax(Resources::SceneNode* object, Visual::Camera* camera)
	{
		LibMath::Vec3 result;

		for (int i = 0; i < object->getModel()->vertexBuffer.size(); ++i)
		{
			LibMath::Vec4 check = convertCoord(LibMath::Vec4(object->getModel()->vertexBuffer[i].position), object->local.m_transform);

			if (i == 0)
			{
				result = check;
			}

			if (check.x > result.x)
				result.x = check.x;

			if (check.y > result.y)
				result.y = check.y;

			if (check.z > result.z)
				result.z = check.z;
		}

		return result;
	}
	
	LibMath::Vec4 convertCoord(LibMath::Vec4 Position, LibMath::Mat4 transform)
	{
		LibMath::Vec4 result = (Position * transform);

		return result;
	}

	//Box::Box(Resources::SceneNode* object)
	//{
	//	for (int i = 0; i < object->_model->vertexBuffer.size(); ++i)
	//	{
	//		LibMath::Vec4 result = LibMath::Vec4(object->_model->vertexBuffer[i].position) * object->local.m_transform;
	//		this->BoxPos.push_back(result);
	//	}
	//}
}

