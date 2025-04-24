#include "Physics/transform.h"

namespace Physics
{
	///Create an Identity Matrice by default
	Transform::Transform(void)
	{
		this->m_transform = LibMath::Mat4::Identity();
	}
	///Associate the current matrix with the givem matrix
	Transform& Transform::translate(const LibMath::Vec3& position)
	{
		this->m_transform *= LibMath::Mat4::Rotate(position);
		return *this;
	}

	///Multiply the matrix by a rotate matrix
	Transform& Transform::rotate(const LibMath::Vec3& movement)
	{
		this->m_transform *= LibMath::Mat4::Rotate(movement);
		return *this;
	}

	///Multiply the matrix by a scaling matrix
	Transform& Transform::scale(const LibMath::Vec3& scaling)
	{
		this->m_transform *= LibMath::Mat4::Scale(scaling);
		return *this;
	}

	///Multiply the matrix by another
	Transform Transform::operator*(const Transform& toMultiply) const 
	{
		Transform result(this->m_transform);

		result.m_transform *= toMultiply.m_transform;

		return result;
	}

	///Multiply the matrix by another and set the result on this object
	Transform& Transform::operator*=(const Transform& toCheck)
	{
		this->m_transform *= toCheck.m_transform;

		return *this;
	}
}