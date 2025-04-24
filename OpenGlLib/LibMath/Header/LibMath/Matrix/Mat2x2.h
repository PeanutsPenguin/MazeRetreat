#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector/Vec2.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class _Type>
	struct Matrix<2, 2, _Type>
	{
		typedef LibMath::Vector<2, _Type> _ColumnType;
		typedef LibMath::Vector<2, _Type> _RowType;

	public:

		Matrix(void) = default;

		Matrix(const Matrix&) = default;

		Matrix(Matrix&&) = default;

		~Matrix(void) = default;

		explicit Matrix(_Type v);

		Matrix(const _RowType&, const _RowType&);

		Matrix(std::initializer_list<_Type> initList);

		Matrix(std::initializer_list<std::initializer_list<_Type>> initList);


		Matrix<2, 2, _Type>& ToIdentity(void) requires (std::is_arithmetic_v<_Type>);

		Matrix<2, 2, _Type>& Empty(void);

		Matrix<2, 2, _Type> GetTranspose(void) const;

		Matrix<2, 2, _Type>& ToTranspose(void);

		_Type GetDeterminant(void) const;

		_Type GetMinor(size_t row, size_t column) const;


		static Matrix<2, 2, _Type> Zero(void);

		static Matrix<2, 2, _Type> Identity(void) requires (std::is_arithmetic_v<_Type>);


		Matrix<2, 2, _Type>& operator=(const Matrix<2, 2, _Type>&) = default;

		Matrix<2, 2, _Type>& operator=(Matrix<2, 2, _Type>&&) = default;


		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }

		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }


		/*template <size_t _C, class _Other>
			requires std::is_convertible_v<_Other, Matrix<2, _C, _Type>>
		Matrix<2, _C, _Type> operator*(const _Other& rhs) const;*/

		template <size_t _C>
		Matrix<2, _C, _Type> operator*(const Matrix<2, _C, _Type>& rhs) const;

		Matrix<2, 2, _Type>& operator*=(const Matrix<2, 2, _Type>& rhs);

		Matrix<2, 2, _Type> operator*(_Type rhs) const;

		Matrix<2, 2, _Type>& operator*=(_Type rhs);

		Matrix<2, 2, _Type> operator+(const Matrix<2, 2, _Type>& rhs) const;

		Matrix<2, 2, _Type>& operator+=(const Matrix<2, 2, _Type>& rhs);

		Matrix<2, 2, _Type> operator-(const Matrix<2, 2, _Type>& rhs) const;

		Matrix<2, 2, _Type>& operator-=(const Matrix<2, 2, _Type>& rhs);

	private:
		_ColumnType m_matrix[2];
	};

	template <class _Type = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<2, 2, _Type>& matrix);

	using Mat2 = typename Matrix<2, 2, float>;
}

#include <LibMath/Matrix/Mat2x2.hpp>