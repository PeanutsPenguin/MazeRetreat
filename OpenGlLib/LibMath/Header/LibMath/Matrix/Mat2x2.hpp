#pragma once

#include <LibMath/Matrix/Mat2x2.h>

namespace LibMath
{
	template<class _Type>
	Matrix<2, 2, _Type>::Matrix(_Type v)
	{
		for (size_t index = 0; index < 2; ++index)
			for (size_t jindex = 0; jindex < 2; ++jindex)
				if (index == jindex) (*this)[index][jindex] = v;
				else (*this)[index][jindex] = _Type(0);
	}

	template<class _Type>
	Matrix<2, 2, _Type>::Matrix(const _RowType& a, const _RowType& b)
	{
		(*this)[0] = a;
		(*this)[1] = b;
	}

	template<class _Type>
	Matrix<2, 2, _Type>::Matrix(std::initializer_list<_Type> initList)
	{
		if (initList.size() != 2 * 2) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		size_t index = 0;
		for (auto& element : initList)
		{
			for (size_t jindex = 0; jindex < 2; ++jindex)
				this->m_matrix[index][jindex] = std::move(element);

			++index;
		}
	}

	template<class _Type>
	Matrix<2, 2, _Type>::Matrix(std::initializer_list<std::initializer_list<_Type>> initList)
	{
		if (initList.size() != 2 || (initList.begin()->size() != 2)) {
			throw std::invalid_argument("Invalid initializer list dimensions");
		}

		std::size_t index = 0;
		for (auto& row : initList)
		{
			if (row.size() != 2)
			{
				throw std::invalid_argument("Invalid initializer list dimensions");
			}

			std::size_t jindex = 0;
			for (auto& element : row)
			{
				this->m_matrix[index][jindex++] = std::move(element);
			}

			++index;
		}
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<2, 2, _Type>::Zero(void)
	{
		Matrix<2, 2, _Type> matrix;

		for (size_t index = 0; index < 2; ++index)
			for (size_t jindex = 0; jindex < 2; ++jindex)
				matrix[index][jindex] = _Type();

		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<2, 2, _Type>::Identity(void) requires (std::is_arithmetic_v<_Type>)
	{
		Matrix<2, 2, _Type> matrix;

		for (size_t index = 0; index < 2; ++index)
			for (size_t jindex = 0; jindex < 2; ++jindex)
				matrix[index][jindex] = std::move((index == jindex) ? _Type(1) : _Type());

		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::ToIdentity(void)
		requires (std::is_arithmetic_v<_Type>)
	{
		for (size_t index = 0; index < 2; ++index)
			for (size_t jindex = 0; jindex < 2; ++jindex)
				(*this)[index][jindex] = std::move((index == jindex) ? _Type(1) : _Type());

		return *this;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::Empty(void)
	{
		for (size_t index = 0; index < 2; ++index)
			for (size_t jindex = 0; jindex < 2; ++jindex)
				(*this)[index][jindex] = std::move(_Type());

		return *this;
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<2, 2, _Type>::GetTranspose(void) const
	{
		Matrix<2, 2, _Type> matrix;

		for (size_t index = 0; index < 2; ++index)
			for (size_t jindex = 0; jindex < 2; ++jindex)
				matrix[jindex][index] = (*this)[index][jindex];

		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::ToTranspose(void)
	{
		*this = std::move(this->GetTranspose());
		return *this;
	}

	template<class _Type>
	_Type Matrix<2, 2, _Type>::GetDeterminant(void) const
	{
		return ((*this)[0][0] * (*this)[1][1]) - ((*this)[0][1] * (*this)[1][0]);
	}

	template<class _Type>
	_Type Matrix<2, 2, _Type>::GetMinor(size_t row, size_t column) const
	{
		size_t zindex = 0;
		for (size_t index = 0; index < 2; ++index)
		{
			size_t kindex = 0;
			for (size_t jindex = 0; jindex < 2; ++jindex)
			{
				if (index == row || jindex == column) continue;

				return (*this)[index][jindex];
			}
		}

		return _Type(0);
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<2, 2, _Type>::operator*(_Type rhs) const
	{
		Matrix<2, 2, _Type> matrix = *this;

		for (size_t index = 0; index < 2; ++index)
			matrix[index] *= rhs;

		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<2, 2, _Type>::operator+(const Matrix<2, 2, _Type>& rhs) const
	{
		Matrix<2, 2, _Type> matrix = *this;

		for (size_t index = 0; index < 2; ++index)
			matrix[index] += rhs[index];

		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::operator+=(const Matrix<2, 2, _Type>& rhs)
	{
		*this = std::move(this->operator+(rhs));
		return *this;
	}

	template<class _Type>
	Matrix<2, 2, _Type> Matrix<2, 2, _Type>::operator-(const Matrix<2, 2, _Type>& rhs) const
	{
		Matrix<2, 2, _Type> matrix = *this;

		for (size_t index = 0; index < 2; ++index)
			matrix[index] -= rhs[index];

		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::operator-=(const Matrix<2, 2, _Type>& rhs)
	{
		*this = std::move(this->operator-(rhs));
		return *this;
	}

	template<class _Type>
	template<size_t _C>
	Matrix<2, _C, _Type> Matrix<2, 2, _Type>::operator*(const Matrix<2, _C, _Type>& rhs) const
	{
		Matrix<2, _C, _Type> matrix;

		for (size_t index = 0; index < 2; ++index)
		{
			for (size_t jindex = 0; jindex < _C; ++jindex)
			{
				matrix[jindex][index] = std::move(_Type());
				for (size_t kindex = 0; kindex < 2; ++kindex)
					matrix[jindex][index] += (*this)[kindex][index] * rhs[jindex][kindex];
			}
		}
		return matrix;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::operator*=(const Matrix<2, 2, _Type>& rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class _Type>
	Matrix<2, 2, _Type>& Matrix<2, 2, _Type>::operator*=(_Type rhs)
	{
		*this = std::move(this->operator*(rhs));
		return *this;
	}

	template<class _Type>
	std::ostream& operator<<(std::ostream& os, const Matrix<2, 2, _Type>& matrix)
	{
		for (size_t index = 0; index < 2; ++index)
		{
			for (size_t jindex = 0; jindex < 2; ++jindex)
				os << matrix[index][jindex] << '\t';

			os << '\n';
		}

		return os;
	}
}