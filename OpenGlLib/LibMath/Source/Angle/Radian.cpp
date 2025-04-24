#include "LibMath/Angle/Radian.h"
#include "LibMath/Angle/Degree.h"

#include <cmath>
#include <numbers>

namespace LibMath
{
	Radian::operator Degree(void) const
	{
		return Degree(this->degree(false));
	}

	bool operator==(Radian lhs, Degree const& rhs)
	{
		return lhs.radian() == rhs.radian();
	}

	Radian& Radian::operator+=(Radian rhs)
	{
		m_value += rhs.m_value;
		return *this;
	}

	Radian& Radian::operator-=(Radian rhs)
	{
		m_value -= rhs.m_value;
		return *this;
	}

	Radian& Radian::operator*=(float factor)
	{
		m_value *= factor;
		return *this;
	}

	Radian& Radian::operator/=(float factor)
	{
		m_value /= factor;
		return *this;
	}

	void Radian::wrap(bool range)
	{
		m_value = radian(range);
	}

	float Radian::radian(bool range) const
	{
		float result = 0.f;

		if (m_value >= 0.f)
		{
			result = std::fmodf(m_value, 2.f * std::numbers::pi_v<float>);
		}
		else
		{
			result = 2.f * std::numbers::pi_v<float> + std::fmodf(m_value, 2.f * std::numbers::pi_v<float>);
		}

		if (range && result >= std::numbers::pi_v<float>)
		{
			result -= 2.f * std::numbers::pi_v<float>;
		}

		return result;
	}

	float Radian::degree(bool range) const
	{
		float result = this->radian(range);

		result *= 180.f / std::numbers::pi_v<float>;
		return result;
	}

	float Radian::raw() const
	{
		return m_value;
	}

	bool operator>(Radian lhs, Radian rhs)
	{
		return lhs.radian() > rhs.radian();
	}

	bool operator<(Radian lhs, Radian rhs)
	{
		return lhs.radian() < rhs.radian();
	}

	bool operator==(Radian lhs, Radian rhs)
	{
		return lhs.radian() == rhs.radian();
	}

	Radian operator-(Radian rhs)
	{
		return Radian(-rhs.raw());
	}

	Radian operator+(Radian lhs, Radian rhs)
	{
		return Radian(lhs.raw() + rhs.raw());
	}

	Radian operator-(Radian lhs, Radian rhs)
	{
		return Radian(lhs.raw() - rhs.raw());
	}

	Radian operator*(Radian lhs, float rhs)
	{
		return Radian(lhs.raw() * rhs);
	}

	Radian operator/(Radian lhs, float rhs)
	{
		return Radian(lhs.raw() / rhs);
	}

	Radian Literal::operator""_rad(long double value)
	{
		return Radian(static_cast<float>(value));
	}

	Radian Literal::operator""_rad(unsigned long long int value)
	{
		return Radian(static_cast<float>(value));
	}
}