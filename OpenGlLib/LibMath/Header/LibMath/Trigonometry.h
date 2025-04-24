#ifndef __LIBMATH__TRIGONOMETRY_H__
#define __LIBMATH__TRIGONOMETRY_H__

#include <cmath>
#include "Angle/Radian.h"

namespace LibMath
{
	extern float const g_pi;	 // useful constant pi -> 3.141592...
	extern float const g_two_pi;

	float	sin(Radian rad);		// float result = sin(Radian{0.5});		// 0.479426
	float	cos(Radian rad);		// float result = sin(Degree{45});		// 0.707107			// this make use implicit conversion
	float	tan(Radian rad);		// float result = sin(0.5_rad);			// 0.479426			// this make use user defined litteral
	Radian	asin(float sin);		// Radian angle = asin(0.479426);		// Radian{0.500001}
	Radian	acos(float cos);		// Degree angle = acos(0.707107);		// Degree{44.99998}	// this make use implicit conversion
	Radian	atan(float tan);		// Radian angle = atan(0.546302);		// Radian{0.500000}
	Radian	atan(float a, float b); // Radian angle = atan(1, -2);			// Radian{2.677945}
}

#endif // !__LIBMATH__TRIGONOMETRY_H__
