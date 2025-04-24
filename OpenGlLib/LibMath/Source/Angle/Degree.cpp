#include "LibMath/Angle/Degree.h"
#include "LibMath/Angle/Radian.h"

#include <cmath>
#include <numbers>

namespace LibMath
{
	Degree::operator Radian(void) const
	{
		return Radian(this->radian(false));
	}

	bool operator==(Degree lhs, Radian const& rhs)
	{
		return lhs.degree() == rhs.degree();
	}

	Degree& Degree::operator+=(Degree rhs)
	{
		m_value += rhs.m_value;
		return *this;
	}

	Degree& Degree::operator-=(Degree rhs)
	{
		m_value -= rhs.m_value;
		return *this;
	}

	Degree& Degree::operator*=(float factor)
	{
		m_value *= factor;
		return *this;
	}

	Degree& Degree::operator/=(float factor)
	{
		m_value /= factor;
		return *this;
	}

	void Degree::wrap(bool range)
	{
		m_value = degree(range);
	}

	float Degree::degree(bool range) const
	{
		int int_degree = (int)m_value;
		float decimal_part = m_value - int_degree;
		float result = 0;

		if (int_degree >= 0)
		{
			result = (int_degree % 360) + decimal_part;
		}
		else
		{
			result = 360 + (int_degree % 360) + decimal_part;
		}

		if (range && result >= 180)
		{
			result -= 360;
		}

		return result;
	}

	float Degree::radian(bool range) const
	{
		float result = degree(range);

		result *= std::numbers::pi_v<float> / 180.f;
		return result;
	}

	float Degree::raw(void) const
	{
		return this->m_value;
	}

	bool operator>(Degree lhs, Degree rhs)
	{
		return lhs.degree(true) > rhs.degree(true);
	}

	bool operator<(Degree lhs, Degree rhs)
	{
		return lhs.degree(true) < rhs.degree(true);
	}

	bool operator==(Degree lhs, Degree rhs)
	{
		return lhs.degree() == rhs.degree();
	}

	Degree operator-(Degree rhs)
	{
		return Degree(-rhs.raw());
	}

	Degree operator+(Degree lhs, Degree rhs)
	{
		return Degree(lhs.raw() + rhs.raw());
	}

	Degree operator-(Degree lhs, Degree rhs)
	{
		return Degree(lhs.raw() - rhs.raw());
	}

	Degree operator*(Degree lhs, float rhs)
	{
		return Degree(lhs.raw() * rhs);
	}

	Degree operator/(Degree lhs, float rhs)
	{
		return Degree(lhs.raw() / rhs);
	}

	Degree Literal::operator""_deg(long double value)
	{
		return Degree(static_cast<float>(value));
	}

	Degree Literal::operator""_deg(unsigned long long int value)
	{
		return Degree(static_cast<float>(value));
	}
}