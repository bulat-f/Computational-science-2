#ifndef VECTOR_H_
#define VECTOR_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "helpers.h"

namespace KFU
{
	enum class Orientation
	{
		vertical, horizontal
	};

	template <class type>
	class Vector;

	template <class type>
	std::ostream& operator<<(std::ostream&, const Vector<type>&);

	template <class type>
	std::istream& operator>>(std::istream&, Vector<type>&);


	template <class type>
	class Vector {
		public:
			Vector();
			Vector(int);
			Vector(int, const type&);
			Vector(type *, int, Orientation);
			Vector(const Vector&);

			int size() const;

			bool empty() const;

			double norm() const;
			double sqr() const;

			void resize(int);
			void swap(int, int);
			void generate();

			Vector& swap(Vector&);

			type operator[](int) const;
			type& operator[](int);
			Vector& operator=(const Vector&);
			Vector& operator+(const Vector&);
			Vector& operator-(const Vector&);
			type operator*(const Vector&);
			Vector& operator+=(const Vector&);
			Vector& operator-=(const Vector&);
			Vector& operator*(type);
			Vector& operator/(type);
		protected:
			std::vector<type> values;
			Orientation orient;
			friend std::ostream& operator<<<type>(std::ostream&, const Vector&);
			friend std::istream& operator>><type>(std::istream&, Vector&);
	};

	template <class type>
	Vector<type>::Vector(): values(), orient(Orientation::horizontal)
	{
	}

	template <class type>
	Vector<type>::Vector(int size): values(size), orient(Orientation::horizontal)
	{
	}

	template <class type>
	Vector<type>::Vector(int size, const type& val): values(size, val), orient(Orientation::horizontal)
	{
	}

	template <class type>
	Vector<type>::Vector(type *array, int size, Orientation o = Orientation::horizontal): values(array, array + size), orient(o)
	{
	}

	template <class type>
	Vector<type>::Vector(const Vector& other): values(other.values), orient(other.orient)
	{
	}

	template <class type>
	int Vector<type>::size() const
	{
		return values.size();
	}

	template <class type>
	bool Vector<type>::empty() const
	{
		return values.empty();
	}

	template <class type>
	double Vector<type>::norm() const
	{
		double result(0);
		for (int i = 0; i < size(); i++)
			result += values[i] * values[i];

		return sqrt(result);
	}

	template <class type>
	double Vector<type>::sqr() const
	{
		double result(0);
		for (int i = 0; i < size(); i++)
			result += values[i] * values[i];

		return result;
	}

	template <class type>
	void Vector<type>::resize(int size)
	{
		values.resize(size);
	}

	template <class type>
	void Vector<type>::swap(int i, int j)
	{
		typename std::vector<type>::iterator first = values.begin() + i;
		typename std::vector<type>::iterator second = values.begin() + j;
		std::swap_ranges(first, first + 1, second);
	}

	template <class type>
	void Vector<type>::generate()
	{
		for (int i = 0; i < size(); i++)
		{
			values[i] = helpers::f(i, size() + 1) * pow(helpers::h(size() + 1), 2);
		}
	}

	template <class type>
	Vector<type>& Vector<type>::swap(Vector& other)
	{
		std::swap((*this), other);
		return other;
	}

	template <class type>
	type Vector<type>::operator[](int i) const
	{
		return values[i];
	}

	template <class type>
	type& Vector<type>::operator[](int i)
	{
		return values[i];
	}

	template <class type>
	Vector<type>& Vector<type>::operator=(const Vector& other)
	{
		values = other.values;
		return *this;
	}

	template <class type>
	Vector<type>& Vector<type>::operator+(const Vector& other)
	{
		Vector<type> *result = new Vector<type>(size());
		for (int i = 0; i < size(); i++)
			(*result)[i] = (*this)[i] + other[i];
		return *result;
	}

	template <class type>
	Vector<type>& Vector<type>::operator-(const Vector& other)
	{
		Vector<type> *result = new Vector<type>(size());
		for (int i = 0; i < size(); i++)
			(*result)[i] = (*this)[i] - other[i];
		return *result;
	}

	template <class type>
	type Vector<type>::operator*(const Vector& other)
	{
		type result(0);
		for (int i = 0; i < size(); i++)
			result += (*this)[i] * other[i];
		return result;
	}

	template <class type>
	Vector<type>& Vector<type>::operator+=(const Vector& other)
	{
		for (int i = 0; i < size(); i++)
			(*this)[i] += other[i];
		return *this;
	}

	template <class type>
	Vector<type>& Vector<type>::operator-=(const Vector& other)
	{
		for (int i = 0; i < size(); i++)
			(*this)[i] -= other[i];
		return *this;
	}

	template <class type>
	Vector<type>& Vector<type>::operator*(type scalar)
	{
		Vector<type> *result = new Vector<type>(size());
		for (int i = 0; i < size(); i++)
			(*result)[i] = (*this)[i] * scalar;
		return *result;
	}

	template <class type>
	Vector<type>& Vector<type>::operator/(type scalar)
	{
		Vector<type> *result = new Vector<type>(size());
		for (int i = 0; i < size(); i++)
			(*result)[i] = (*this)[i] / scalar;
		return *result;
	}

	template <class type>
	std::ostream& operator<<(std::ostream& out, const Vector<type>& data)
	{
		char separator = (' ');
		for (int i = 0; i < data.size(); i++)
			out << data[i] << separator;
		out << std::endl;
		return out;
	}

	template <class type>
	std::istream& operator>>(std::istream& in, Vector<type>& data)
	{
		for (int i = 0; i < data.size(); i++)
			in >> data[i];
		return in;
	}
}

#endif
