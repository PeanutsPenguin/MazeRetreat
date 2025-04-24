#include "LibMath/Trigonometry.h"

namespace LibMath
{
	extern float const g_pi = 3.1415927F;
	extern float const g_two_pi = 6.2831855F;

	float	sin(Radian rad) { return std::sinf(rad.radian(true)); }
	float	cos(Radian rad) { return std::cosf(rad.radian(true)); }
	float	tan(Radian rad) { return std::tanf(rad.radian(true)); }
	Radian	asin(float sin) { return LibMath::Radian(std::asinf(sin)); }
	Radian	acos(float cos) { return LibMath::Radian(std::acosf(cos)); }
	Radian	atan(float tan) { return LibMath::Radian(std::atanf(tan)); }
	Radian	atan(float a, float b) { return LibMath::Radian(std::atan2f(a, b)); }
}