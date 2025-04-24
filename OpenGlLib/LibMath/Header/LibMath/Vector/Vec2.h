#pragma once

#include "LibMath/Angle/Radian.h"
#include <LibMath/Vector/Vec1.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<2, _Type>
	{
		Vector(void);

		explicit Vector(_Type value);

		Vector(_Type x, _Type y);

		Vector(const Vector<1, _Type>& a, const Vector<1, _Type>& b);

		Vector(const Vector<2, _Type>&) = default;

		Vector(Vector<2, _Type>&&) = default;

		~Vector(void) = default;



		static Vector<2, _Type>	Zero(void);

		static Vector<2, _Type>	One(void);

		static Vector<2, _Type>	Down(void);

		static Vector<2, _Type>	Left(void);

		static Vector<2, _Type>	Right(void);


		static LibMath::Radian		Angle(const Vector<2, _Type>&, const Vector<2, _Type>&);

		static _Type				Distance(const Vector<2, _Type>&, const Vector<2, _Type>&);

		static _Type				DistanceSquared(const Vector<2, _Type>&, const Vector<2, _Type>&);

		static int					Compare(const Vector<2, _Type>&, const Vector<2, _Type>&);

		static bool					IsUnit(const Vector<2, _Type>&);

		static Vector<2, _Type>		Normalize(const Vector<2, _Type>&);

		static Vector<2, _Type>		Project(const Vector<2, _Type>&, const Vector<2, _Type>&);

		static Vector<2, _Type>		Reflect(const Vector<2, _Type>&, const Vector<2, _Type>&);

		static _Type				Dot(const Vector<2, _Type>&, const Vector<2, _Type>&);


		operator Vector<4, _Type>() const;

		operator Vector<3, _Type>() const;

		operator Vector<1, _Type>() const;


		Vector<2, _Type>&	operator=(const Vector<2, _Type>&) = default;

		Vector<2, _Type>&	operator=(Vector<2, _Type>&&) = default;

		_Type&				operator[](size_t index);

		const _Type&		operator[](size_t index) const;

		bool				operator==(const Vector<2, _Type>&) const;

		bool				operator!=(const Vector<2, _Type>&) const;

		Vector<2, _Type>&	operator++(void);

		Vector<2, _Type>	operator++(int) const;

		Vector<2, _Type>&	operator--(void);

		Vector<2, _Type>	operator--(int) const;

		Vector<2, _Type>	operator+(const Vector<2, _Type>&) const;

		Vector<2, _Type>&	operator+=(const Vector<2, _Type>&);

		Vector<2, _Type>	operator+(_Type) const;

		Vector<2, _Type>&	operator+=(_Type);

		Vector<2, _Type>	operator-(const Vector<2, _Type>&) const;

		Vector<2, _Type>&	operator-=(const Vector<2, _Type>&);

		Vector<2, _Type>	operator-(void) const;

		Vector<2, _Type>	operator-(_Type) const;

		Vector<2, _Type>&	operator-=(_Type);

		Vector<2, _Type>&	operator*=(const Vector<2, _Type>&);

		Vector<2, _Type>	operator*(const Vector<2, _Type>&) const;

		Vector<2, _Type>&	operator*=(_Type);

		Vector<2, _Type>	operator*(_Type) const;

		Vector<2, _Type>&	operator/=(const Vector<2, _Type>&);

		Vector<2, _Type>	operator/(const Vector<2, _Type>&) const;

		Vector<2, _Type>&	operator/=(_Type);

		Vector<2, _Type>	operator/(_Type) const;



		_Type	Magnitude(void) const;

		_Type	MagnitudeSquared(void) const;

		union { _Type x, r, s; };
		union { _Type y, g, t; };
	};

	template <typename _Type>
	std::ostream& operator<<(std::ostream&, const Vector<2, _Type>&);

	template <typename _Type>
	std::istream& operator>>(std::istream&, Vector<2, _Type>&);


	using Vec2 = typename Vector<2, float>;
}

#include <LibMath/Vector/Vec2.hpp>