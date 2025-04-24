#ifndef __LIBMATH__QUATERNION_H__
#define __LIBMATH__QUATERNION_H__

#include "LibMath/Vector/Vec4.h"
#include "LibMath/Matrix/Matrix.h"

namespace LibMath
{
	class Quaternion
	{
		float m_x;
		float m_y;
		float m_z;
		float m_w;
	};

	Quaternion operator+(Quaternion, Quaternion const&);
	Quaternion operator*(Quaternion const&, Quaternion const&);
	Quaternion operator*(Quaternion, float);
	Quaternion conjugate(Quaternion const&);
	Quaternion normalize(Quaternion const&);
	Quaternion slerp(Quaternion const&, Quaternion const&, float);

	Vec4 rotatePoint(Quaternion const&, Vec4 const&);

	//Matrix4 toMatrix4(Quaternion const&);
}

#endif // !__LIBMATH__QUATERNION_H__
