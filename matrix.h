#ifndef MATRIX_H_
#define MATRIX_H_

#include <fstream>
#include <iostream>
#include "vector.h"
#include "helpers.h"


namespace KFU
{
	template <class type>
	class Matrix;

	template <class type>
	std::ostream& operator<<(std::ostream&, const Matrix<type>&);

	template <class type>
	std::istream& operator>>(std::istream&, Matrix<type>&);

	template <class type>
	class Matrix
	{
		public:
			Matrix();
			Matrix(int);
			Matrix(int, int);
			Matrix(type **, const int &, const int &);
			Matrix(const Matrix &);

			int rows() const;
			int columns() const;

			type getElem(int, int) const;

			void resize(int, int);
			void swap_lines(int, int);
			void generate();

			Matrix& operator=(const Matrix&);
			Vector<type>& operator*(const Vector<type>&);
			Vector<type>& operator[](int);
		private:
			Vector<Vector<type>> values;

			double a(int);

			friend std::ostream& operator<<<type>(std::ostream&, const Matrix&);
			friend std::istream& operator>><type>(std::istream&, Matrix&);
	};

	template <class type>
	Matrix<type>::Matrix(): values()
	{
	}

	template <class type>
	Matrix<type>::Matrix(int n): values(n, Vector<type>(n))
	{
	}


	template <class type>
	Matrix<type>::Matrix(int rows, int columns): values(rows, Vector<type>(columns))
	{
	}

	template <class type>
	Matrix<type>::Matrix(type **array, const int &n, const int &m): values(n)
	{
		for (int i = 0; i < n; i++)
		{
			values[i].resize(m);
			for (int j = 0; j < m; j++)
				values[i][j] = array[i][j];
		}
	}

	template <class type>
	Matrix<type>::Matrix(const Matrix& other): values(other.values)
	{
	}

	template <class type>
	int Matrix<type>::rows() const
	{
		return values.size();
	}

	template <class type>
	int Matrix<type>::columns() const
	{
		return (values.empty() ? 0 : values[0].size());
	}

	template <class type>
	type Matrix<type>::getElem(int i, int j) const
	{
		return values[i][j];
	}

	template <class type>
	void Matrix<type>::resize(int n, int m)
	{
		values.resize(n);
		for (int i = 0; i < values.size(); i++)
			values[i].resize(m);
	}

	template <class type>
	void Matrix<type>::swap_lines(int i, int j)
	{
		values[i].swap(values[j]);
	}

	template <class type>
	void Matrix<type>::generate()
	{
		int n = rows();
		values[0][0] = values[n - 1][n - 1] = 1;
		for (int i = 1; i < n - 1; i++)
		{
			values[i][i - 1] = -a(i);
			values[i][i] = a(i) + a(i + 1) + helpers::g(i) * pow(helpers::h(rows()), 2);
			values[i][i + 1] = -a(i + 1);
		}
	}

	template <class type>
	Matrix<type>& Matrix<type>::operator=(const Matrix& other)
	{
		values = other.values;
		return *this;
	}

	template <class type>
	Vector<type>& Matrix<type>::operator*(const Vector<type>& multiplier) // Пока будем считать, что всегда задается вектор столбец
	{
		int m = rows(), n = columns();
		Vector<type> *result = new Vector<type>(m);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				(*result)[i] += values[i][j] * multiplier[j];
		return *result;
	}

	template <class type>
	Vector<type>& Matrix<type>::operator[](int i)
	{
		return values[i];
	}

	template <class type>
	double Matrix<type>::a(int i)
	{
		return helpers::p(i * helpers::h(rows()));
	}

	template <class type>
	std::ostream& operator<<(std::ostream& out, const Matrix<type>& data)
	{
		for (int i = 0; i < data.rows(); i++)
		{
			for (int j = 0; j < data.columns(); j++)
				out << data.values[i][j] << ' ';
			out << std::endl;
		}
		return out;
	}

	template <class type>
	std::istream& operator>>(std::istream& in, Matrix<type>& data)
	{
		for (int i = 0; i < data.rows(); i++)
		{
			for (int j = 0; j < data.columns(); j++)
				in >> data.values[i][j];
		}
		return in;
	}
}

#endif
