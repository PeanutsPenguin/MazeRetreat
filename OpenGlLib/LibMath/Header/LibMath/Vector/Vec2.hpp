#pragma once

#include <LibMath/Trigonometry.h>
#include <LibMath/Vector/Vec2.h>

#include <float.h>

#define EPSILON FLT_EPSILON
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

namespace LibMath
{
	template<typename _Type>
	inline LibMath::Vector<2, _Type>::Vector(void) : LibMath::Vector<2, _Type>(_Type(0)) {}

	template<typename _Type>
	inline LibMath::Vector<2, _Type>::Vector(_Type value) : LibMath::Vector<2, _Type>(value, value) {}

	template<typename _Type>
	inline LibMath::Vector<2, _Type>::Vector(_Type x, _Type y) : x(x), y(y) {}

	template<typename _Type>
	inline LibMath::Vector<2, _Type>::Vector(const Vector<1, _Type>& a, const Vector<1, _Type>& b) : x(a.x), y(b.x) { }

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Zero(void)
	{
		return Vector<2, _Type>();
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::One(void)
	{
		return Vector<2, _Type>(1);
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Down(void)
	{
		return Vector<2, _Type>(0, -1);
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Left(void)
	{
		return Vector<2, _Type>(-1, 0);
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Right(void)
	{
		return Vector<2, _Type>(1, 0);
	}

	template<typename _Type>
	inline LibMath::Radian LibMath::Vector<2, _Type>::Angle(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		return LibMath::acos(LibMath::Vec2::Dot(LibMath::Vec2::Normalize(a), LibMath::Vec2::Normalize(b)));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<2, _Type>::Distance(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		return b.operator-(a).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<2, _Type>::DistanceSquared(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		return b.operator-(a).MagnitudeSquared();
	}

	template<typename _Type>
	inline int LibMath::Vector<2, _Type>::Compare(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		_Type m_a = a.Magnitude(), m_b = b.Magnitude();
		return m_a < m_b ? 1 : m_a > m_b ? -1 : 0;
	}

	template<typename _Type>
	inline bool LibMath::Vector<2, _Type>::IsUnit(const Vector<2, _Type>& vec)
	{
		return FLOAT_EQ(vec.Magnitude(), _Type(1));
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Normalize(const Vector<2, _Type>& vec)
	{
		return vec.operator/(vec.Magnitude());
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Project(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		return b * (LibMath::Vec2::Dot(a, b) / LibMath::Vec2::Dot(b, b));
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::Reflect(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		LibMath::Vec2 N = LibMath::Vec2::Normalize(b);
		return a - N * LibMath::Vec2::Dot(N, a) * static_cast<_Type>(2);
	}

	template<typename _Type>
	inline _Type LibMath::Vector<2, _Type>::Dot(const Vector<2, _Type>& a, const Vector<2, _Type>& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	template<typename _Type>
	inline LibMath::Vector<2, _Type>::operator Vector<4, _Type>() const
	{
		return Vector<4, _Type>(this->x, this->y, static_cast<_Type>(0), static_cast<_Type>(1));
	}

	template<typename _Type>
	inline LibMath::Vector<2, _Type>::operator Vector<3, _Type>() const
	{
		return Vector<3, _Type>(this->x, this->y, static_cast<_Type>(0));
	}

	template<typename _Type>
	inline LibMath::Vector<2, _Type>::operator Vector<1, _Type>() const
	{
		return Vector<1, _Type>(this->x);
	}

	template<typename _Type>
	inline _Type& LibMath::Vector<2, _Type>::operator[](size_t index)
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		case 1:
			return this->y;
		}
	}

	template<typename _Type>
	inline const _Type& LibMath::Vector<2, _Type>::operator[](size_t index) const
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		case 1:
			return this->y;
		}
	}

	template<typename _Type>
	inline bool LibMath::Vector<2, _Type>::operator==(const Vector<2, _Type>& vec) const
	{
		return this->x == vec.x && this->y == vec.y;
	}

	template<typename _Type>
	inline bool LibMath::Vector<2, _Type>::operator!=(const Vector<2, _Type>& vec) const
	{
		return this->x != vec.x || this->y != vec.y;
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator++(void)
	{
		++this->x;
		++this->y;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator++(int) const
	{
		return Vector<2, _Type>(this->x++, this->y++);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator--(void)
	{
		--this->x;
		--this->y;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator--(int) const
	{
		return Vector<2, _Type>(this->x--, this->y--);
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator+(const Vector<2, _Type>& vec) const
	{
		return Vector<2, _Type>(this->x + vec.x, this->y + vec.y);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator+=(const Vector<2, _Type>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator+(_Type scalar) const
	{
		return Vector<2, _Type>(this->x + scalar, this->y + scalar);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator+=(_Type scalar)
	{
		this->x += scalar;
		this->y += scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator-(const Vector<2, _Type>& vec) const
	{
		return Vector<2, _Type>(this->x - vec.x, this->y - vec.y);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator-=(const Vector<2, _Type>& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator-(void) const
	{
		return Vector<2, _Type>(-this->x, -this->y);
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator-(_Type scalar) const
	{
		return Vector<2, _Type>(this->x - scalar, this->y - scalar);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator-=(_Type scalar)
	{
		this->x -= scalar;
		this->y -= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator*(const Vector<2, _Type>& vec) const
	{
		return Vector<2, _Type>(this->x * vec.x, this->y * vec.y);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator*=(const Vector<2, _Type>& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator*(_Type scalar) const
	{
		return Vector<2, _Type>(this->x * scalar, this->y * scalar);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator*=(_Type scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator/(const Vector<2, _Type>& vec) const
	{
		return Vector<2, _Type>(this->x / vec.x, this->y / vec.y);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator/=(const Vector<2, _Type>& vec)
	{
		this->x /= vec.x;
		this->y /= vec.y;
		return *this;
	}

	template<typename _Type>
	inline Vector<2, _Type> LibMath::Vector<2, _Type>::operator/(_Type scalar) const
	{
		return Vector<2, _Type>(this->x / scalar, this->y / scalar);
	}

	template<typename _Type>
	inline Vector<2, _Type>& LibMath::Vector<2, _Type>::operator/=(_Type scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		return *this;
	}

	template<typename _Type>
	inline _Type LibMath::Vector<2, _Type>::Magnitude(void) const
	{
		return std::sqrtf(std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<2, _Type>::MagnitudeSquared(void) const
	{
		return std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f);
	}

	template<typename _Type>
	std::ostream& operator<<(std::ostream& os, const Vector<2, _Type>& vec)
	{
		os << "v\t";
		for (size_t index = 0; index < 2; ++index)
		{
			os << vec[index] << '\t';
		}
		return os;
	}

	template<typename _Type>
	std::istream& operator>>(std::istream& is, Vector<2, _Type>& vec)
	{
		for (size_t index = 0; index < 2; ++index)
		{
			if (!(is >> vec[index]))
				vec[index] = _Type(0);
		}
		return is;
	}
}