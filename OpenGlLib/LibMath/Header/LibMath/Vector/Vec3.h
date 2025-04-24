#pragma once

#include <iostream>
#include <string>

#include "LibMath/Angle/Radian.h"
#include <LibMath/Vector/Vec2.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<3, _Type>
	{
		Vector(void);

		explicit Vector(_Type value);

		Vector(_Type x, _Type y, _Type z);

		Vector(const Vector<1, _Type>& x, const Vector<1, _Type>& y, const Vector<1, _Type>& z);

		Vector(const Vector<2, _Type>& xy, const Vector<1, _Type>& z);

		Vector(const Vector<1, _Type>& x, const Vector<2, _Type>& yz);

		Vector(const Vector<3, _Type>&) = default;

		Vector(Vector<3, _Type>&&) = default;

		~Vector(void) = default;



		static Vector<3, _Type>	Zero(void);

		static Vector<3, _Type>	One(void);

		static Vector<3, _Type>	Up(void);

		static Vector<3, _Type>	Down(void);

		static Vector<3, _Type>	Left(void);

		static Vector<3, _Type>	Right(void);

		static Vector<3, _Type>	Front(void);

		static Vector<3, _Type>	Back(void);


		static LibMath::Radian		Angle(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static _Type				Distance(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static _Type				Distance2(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static _Type				DistanceSquared(const Vector<3, _Type>&, const Vector<3, _Type>&);
		
		static _Type				Distance2Squared(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static int					Compare(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static bool					IsUnit(const Vector<3, _Type>&);

		static Vector<3, _Type>		Normalize(const Vector<3, _Type>&);

		static Vector<3, _Type>		Project(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static Vector<3, _Type>		Reflect(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static _Type				Dot(const Vector<3, _Type>&, const Vector<3, _Type>&);

		static Vector<3, _Type>		Cross(const Vector<3, _Type>&, const Vector<3, _Type>&);


		operator Vector<4, _Type>() const;

		operator Vector<2, _Type>() const;

		operator Vector<1, _Type>() const;

		Vector<3, _Type>& operator=(const Vector<3, _Type>&) = default;

		Vector<3, _Type>& operator=(Vector<3, _Type>&&) = default;

		_Type& operator[](size_t index);

		const _Type& operator[](size_t index) const;

		bool				operator==(const Vector<3, _Type>&) const;

		bool				operator!=(const Vector<3, _Type>&) const;

		Vector<3, _Type>& operator++(void);

		Vector<3, _Type>	operator++(int) const;

		Vector<3, _Type>& operator--(void);

		Vector<3, _Type>	operator--(int) const;

		Vector<3, _Type>	operator+(const Vector<3, _Type>&) const;

		Vector<3, _Type>& operator+=(const Vector<3, _Type>&);

		Vector<3, _Type>	operator+(_Type) const;

		Vector<3, _Type>& operator+=(_Type);

		Vector<3, _Type>	operator-(const Vector<3, _Type>&) const;

		Vector<3, _Type>& operator-=(const Vector<3, _Type>&);

		Vector<3, _Type>	operator-(void) const;
		
		Vector<3, _Type>	operator-(_Type) const;

		Vector<3, _Type>& operator-=(_Type);

		Vector<3, _Type>& operator*=(const Vector<3, _Type>&);

		Vector<3, _Type>	operator*(const Vector<3, _Type>&) const;

		Vector<3, _Type>& operator*=(_Type);

		Vector<3, _Type>	operator*(_Type) const;

		Vector<3, _Type>& operator/=(const Vector<3, _Type>&);

		Vector<3, _Type>	operator/(const Vector<3, _Type>&) const;

		Vector<3, _Type>& operator/=(_Type);

		Vector<3, _Type>	operator/(_Type) const;


		_Type	Magnitude(void) const;

		_Type	MagnitudeSquared(void) const;



		union { _Type x, r, s; };
		union { _Type y, g, t; };
		union { _Type z, b, p; };
	};

	template <typename _Type>
	std::ostream& operator<<(std::ostream&, const Vector<3, _Type>&);

	template <typename _Type>
	std::istream& operator>>(std::istream&, Vector<3, _Type>&);


	using Vec3 = typename Vector<3, float>;
}

#include <LibMath/Vector/Vec3.hpp>