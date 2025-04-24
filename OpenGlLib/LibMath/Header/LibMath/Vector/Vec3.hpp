#pragma once

#include <LibMath/Trigonometry.h>
#include <LibMath/Vector/Vec3.h>

#include <float.h>

#define EPSILON FLT_EPSILON
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

namespace LibMath
{
	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(void) : LibMath::Vector<3, _Type>(_Type(0)) {}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(_Type value) : LibMath::Vector<3, _Type>(value, value, value) {}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(_Type x, _Type y, _Type z) : x(x), y(y), z(z) {}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(const Vector<1, _Type>& a, const Vector<1, _Type>& b, const Vector<1, _Type>& c) : x(a.x), y(b.x), z(c.z) { }
	
	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(const Vector<2, _Type>& xy, const Vector<1, _Type>& z) : x(xy.x), y(xy.y), z(z.x) { }
	
	template<typename _Type>
	inline LibMath::Vector<3, _Type>::Vector(const Vector<1, _Type>& x, const Vector<2, _Type>& yz) : x(x.x), y(yz.x), z(yz.y) { }

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Zero(void)
	{
		return Vector<3, _Type>();
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::One(void)
	{
		return Vector<3, _Type>(_Type(1));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Up(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(1), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Down(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(-1), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Left(void)
	{
		return Vector<3, _Type>(_Type(-1), _Type(0), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Right(void)
	{
		return Vector<3, _Type>(_Type(1), _Type(0), _Type(0));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Front(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(0), _Type(1));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Back(void)
	{
		return Vector<3, _Type>(_Type(0), _Type(0), _Type(-1));
	}

	template<typename _Type>
	inline LibMath::Radian LibMath::Vector<3, _Type>::Angle(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::acos(LibMath::Vec3::Dot(LibMath::Vec3::Normalize(a), LibMath::Vec3::Normalize(b)));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::Distance(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return b.operator-(a).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::Distance2(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::Vector<2, _Type>(b).operator-(LibMath::Vector<2, _Type>(a)).Magnitude();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::DistanceSquared(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return b.operator-(a).MagnitudeSquared();
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::Distance2Squared(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::Vector<2, _Type>(b).operator-(LibMath::Vector<2, _Type>(a)).MagnitudeSquared();
	}

	template<typename _Type>
	inline int LibMath::Vector<3, _Type>::Compare(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		_Type m_a = a.Magnitude(), m_b = b.Magnitude();
		return m_a < m_b ? 1 : m_a > m_b ? -1 : 0;
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::IsUnit(const Vector<3, _Type>& vec)
	{
		return FLOAT_EQ(vec.Magnitude(), _Type(1));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Normalize(const Vector<3, _Type>& vec)
	{
		return vec.operator/(vec.Magnitude());
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Project(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return b * (LibMath::Vec3::Dot(a, b) / LibMath::Vec3::Dot(b, b));
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::Reflect(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		LibMath::Vec3 N = LibMath::Vec3::Normalize(b);
		return a - N * LibMath::Vec3::Dot(N, a) * static_cast<_Type>(2);
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::Dot(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type> LibMath::Vector<3, _Type>::Cross(const Vector<3, _Type>& a, const Vector<3, _Type>& b)
	{
		return LibMath::Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::operator Vector<4, _Type>() const
	{
		return Vector<4, _Type>(this->x, this->y, this->z, static_cast<_Type>(1));
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::operator Vector<2, _Type>() const
	{
		return Vector<2, _Type>(this->x, this->y);
	}

	template<typename _Type>
	inline LibMath::Vector<3, _Type>::operator Vector<1, _Type>() const
	{
		return Vector<1, _Type>(this->x);
	}

	template<typename _Type>
	inline _Type& LibMath::Vector<3, _Type>::operator[](size_t index)
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		}
	}

	template<typename _Type>
	inline const _Type& LibMath::Vector<3, _Type>::operator[](size_t index) const
	{
		switch (index)
		{
		default:
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		}
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::operator==(const Vector<3, _Type>& vec) const
	{
		return this->x == vec.x && this->y == vec.y && this->z == vec.z;
	}

	template<typename _Type>
	inline bool LibMath::Vector<3, _Type>::operator!=(const Vector<3, _Type>& vec) const
	{
		return this->x != vec.x || this->y != vec.y || this->z != vec.z;
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator++(void)
	{
		++this->x;
		++this->y;
		++this->z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator++(int) const
	{
		return Vector<3, _Type>(this->x++, this->y++, this->z++);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator--(void)
	{
		--this->x;
		--this->y;
		--this->z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator--(int) const
	{
		return Vector<3, _Type>(this->x--, this->y--, this->z--);
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator+(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator+=(const Vector<3, _Type>& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator+(_Type scalar) const
	{
		return Vector<3, _Type>(this->x + scalar, this->y + scalar, this->z + scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator+=(_Type scalar)
	{
		this->x += scalar;
		this->y += scalar;
		this->z += scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator-(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator-=(const Vector<3, _Type>& vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator-(void) const
	{
		return Vector<3, _Type>(-this->x, -this->y, -this->z);
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator-(_Type scalar) const
	{
		return Vector<3, _Type>(this->x - scalar, this->y - scalar, this->z - scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator-=(_Type scalar)
	{
		this->x -= scalar;
		this->y -= scalar;
		this->z -= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator*(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator*=(const Vector<3, _Type>& vec)
	{
		this->x *= vec.x;
		this->y *= vec.y;
		this->z *= vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator*(_Type scalar) const
	{
		return Vector<3, _Type>(this->x * scalar, this->y * scalar, this->z * scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator*=(_Type scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator/(const Vector<3, _Type>& vec) const
	{
		return Vector<3, _Type>(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator/=(const Vector<3, _Type>& vec)
	{
		this->x /= vec.x;
		this->y /= vec.y;
		this->z /= vec.z;
		return *this;
	}

	template<typename _Type>
	inline Vector<3, _Type> LibMath::Vector<3, _Type>::operator/(_Type scalar) const
	{
		return Vector<3, _Type>(this->x / scalar, this->y / scalar, this->z/ scalar);
	}

	template<typename _Type>
	inline Vector<3, _Type>& LibMath::Vector<3, _Type>::operator/=(_Type scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		return *this;
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::Magnitude(void) const
	{
		return std::sqrtf(std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f) + std::powf(static_cast<float>(this->z), 2.f));
	}

	template<typename _Type>
	inline _Type LibMath::Vector<3, _Type>::MagnitudeSquared(void) const
	{
		return std::powf(static_cast<float>(this->x), 2.f) + std::powf(static_cast<float>(this->y), 2.f) + std::powf(static_cast<float>(this->z), 2.f);
	}

	template<typename _Type>
	std::ostream& operator<<(std::ostream& os, const Vector<3, _Type>& vec)
	{
		os << "v\t";
		for (size_t index = 0; index < 3; ++index)
		{
			os << vec[index] << '\t';
		}
		return os;
	}

	template<typename _Type>
	std::istream& operator>>(std::istream& is, Vector<3, _Type>& vec)
	{
		for (size_t index = 0; index < 3; ++index)
		{
			if (!(is >> vec[index])) 
				vec[index] = _Type(0);
		}
		return is;
	}
}