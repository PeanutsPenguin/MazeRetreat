#pragma once

#include <LibMath/Vector/Vector.h>

namespace LibMath
{
	template <typename _Type>
	struct Vector<1, _Type>
	{
		Vector(void);

		explicit Vector(_Type value);

		Vector(const Vector<1, _Type>&) = default;

		Vector(Vector<1, _Type>&&) = default;

		~Vector(void) = default;

		static Vector<1, _Type>	Zero(void);

		static Vector<1, _Type>	One(void);

		Vector<1, _Type>& operator=(const Vector<1, _Type>&) = default;

		Vector<1, _Type>& operator=(Vector<1, _Type>&&) = default;

		_Type&	operator[](size_t index);

		const _Type&	operator[](size_t index) const;

		union { _Type x, r, s; };
	};

	using Vec1 = typename Vector<1, float>;
}

#include <LibMath/Vector/Vec1.hpp>