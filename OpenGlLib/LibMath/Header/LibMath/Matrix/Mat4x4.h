#pragma once

#include "LibMath/Trigonometry.h"

#include "exception"
#include <iostream>

#include <type_traits>
#include <initializer_list>

#include <LibMath/Vector/Vec4.h>
#include <LibMath/Matrix/Matrix.h>

namespace LibMath
{
	template <class _Type>
	struct Matrix<4, 4, _Type> 
	{
		typedef LibMath::Vector<4, _Type> _ColumnType;
		typedef LibMath::Vector<4, _Type> _RowType;

	public:

		Matrix(void) = default;

		Matrix(const Matrix&) = default;

		Matrix(Matrix&&) = default;

		~Matrix(void) = default;

		explicit Matrix(_Type v);

		Matrix(const _RowType&, const _RowType&, const _RowType&, const _RowType&);

		Matrix(std::initializer_list<_Type> initList);

		Matrix(std::initializer_list<std::initializer_list<_Type>> initList);


		Matrix<4, 4, _Type>& ToIdentity(void) requires (std::is_arithmetic_v<_Type>);

		Matrix<4, 4, _Type>& Empty(void);

		Matrix<4, 4, _Type> GetTranspose(void) const;

		Matrix<4, 4, _Type>& ToTranspose(void);

		_Type GetDeterminant(void) const;

		Matrix<3, 3, _Type> GetMinor(size_t row, size_t column) const;

		Matrix<4, 4, _Type> GetMinorsDeterminant(void) const;

		Matrix<4, 4, _Type> GetCofactors(void) const;

		Matrix<4, 4, _Type> GetInverse(void) const;


		static Matrix<4, 4, _Type> Zero(void);
		
		static Matrix<4, 4, _Type> Identity(void) requires (std::is_arithmetic_v<_Type>);

		static Matrix<4, 4, _Type> Translate(const LibMath::Vector<3, _Type>&) requires (std::is_arithmetic_v<_Type>);

		static Matrix<4, 4, _Type> Rotate(const LibMath::Vector<3, _Type>&) requires (std::is_arithmetic_v<_Type>);

		static Matrix<4, 4, _Type> Scale(const LibMath::Vector<3, _Type>&) requires (std::is_arithmetic_v<_Type>);

		static Matrix<4, 4, _Type> Perspective(_Type fov, _Type aspect, _Type near, _Type far) requires (std::is_arithmetic_v<_Type>);

		static Matrix<4, 4, _Type> LookAt(const LibMath::Vec3&, const LibMath::Vec3&, const LibMath::Vec3&);



		Matrix<4, 4, _Type>& operator=(const Matrix<4, 4, _Type>&) = default;

		bool operator==(const Matrix<4, 4, _Type>&) const = default;

		Matrix<4, 4, _Type>& operator=(Matrix<4, 4, _Type>&&) = default;


		_ColumnType& operator[](size_t index) noexcept { return this->m_matrix[index]; }

		const _ColumnType& operator[](size_t index) const noexcept { return this->m_matrix[index]; }


		/*template <size_t _C, class _Other>
		Matrix<4, _C, _Type> operator*(const _Other& rhs) const;*/

		template <size_t _C>
		Matrix<4, _C, _Type> operator*(const Matrix<4, _C, _Type>& rhs) const;

		Matrix<4, 4, _Type>& operator*=(const Matrix<4, 4, _Type>& rhs);

		Matrix<4, 4, _Type> operator*(_Type rhs) const;

		Matrix<4, 4, _Type>& operator*=(_Type rhs);

		Matrix<4, 4, _Type> operator+(const Matrix<4, 4, _Type>& rhs) const;

		Matrix<4, 4, _Type>& operator+=(const Matrix<4, 4, _Type>& rhs);

		Matrix<4, 4, _Type> operator-(const Matrix<4, 4, _Type>& rhs) const;

		Matrix<4, 4, _Type>& operator-=(const Matrix<4, 4, _Type>& rhs);

	private:
		_ColumnType m_matrix[4];
	};

	template <class _Type>
	Vector<4, _Type> operator*(const Vector<4, _Type>&, const Matrix<4, 4, _Type>&);

	template <class _Type = float>
	std::ostream& operator<<(std::ostream& os, const Matrix<4, 4, _Type>& matrix);

	using Mat4 = typename Matrix<4, 4, float>;
}

#include <LibMath/Matrix/Mat4x4.hpp>