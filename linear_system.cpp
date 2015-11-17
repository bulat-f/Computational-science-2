#include "linear_system.h"

#include <cmath>

namespace KFU
{
	LinearSystem::LinearSystem()
	{
	}

	LinearSystem::LinearSystem(int n)
	{
		matrix_.resize(n, n);
		vector_.resize(n);
		matrix_.generate();
		vector_.generate();
	}

	LinearSystem::LinearSystem(int n, int m)
	{
		matrix_.resize(n, m);
		vector_.resize(n);
	}

	LinearSystem::LinearSystem(const Matrix<double>& m, const Vector<double>& v)
	{
		matrix_ = m;
		vector_ = v;
	}

	LinearSystem::LinearSystem(const LinearSystem& other)
	{
		matrix_ = other.matrix_;
		vector_ = other.vector_;
	}

	int LinearSystem::equations() const
	{
		return vector_.size();
	}

	int LinearSystem::variables() const
	{
		return matrix_.columns();
	}

	void LinearSystem::swap_lines(int i, int j)
	{
		matrix_.swap_lines(i, j);
		vector_.swap(i, j);
	}

	Vector<double> LinearSystem::solve()
	{
		LinearSystem tmp(*this);
		Vector<double> result(variables());
		double coefficient, sum;
		int max_row;
		for (int i = 0; i < tmp.equations() - 1; i++)
		{
			max_row = i;
			for (int j = i + 1; j < tmp.equations(); j++)
			{
				if (fabs(matrix_[j][i]) > fabs(tmp.matrix_[max_row][i]))
					max_row = j;
			}
			tmp.swap_lines(i, max_row);
			for (int k = i + 1; k < tmp.equations(); k++)
			{
				coefficient = tmp.matrix_[k][i] / tmp.matrix_[i][i];
				tmp.matrix_[k] -= tmp.matrix_[i] * coefficient;
				tmp.vector_[k] -= tmp.vector_[i] * coefficient;
			}
		}
		for (int i = tmp.variables() - 1; i >= 0; i--)
		{
			sum = 0;
			for (int j = i + 1; j < tmp.variables(); j++)
				sum += result[j] * tmp.matrix_[i][j];
			result[i] = (tmp.vector_[i] - sum) / tmp.matrix_[i][i];
		}
		return result;
	}

	Vector<double> LinearSystem::solve2(double eps)
	{
		const int size = variables();
		Vector<double> next(size), current(size), r(size);
		double tau;
		do
		{
			current = next;
			r = matrix_ * current - vector_;
			tau = ((matrix_ * r) * r) / (matrix_ * r).sqr();
			next = current - r * tau;
		} while (r.norm() > eps);
		return next;
	}

	std::ostream& operator<<(std::ostream& out, LinearSystem& sys)
	{
		for (int i = 0; i < sys.equations(); i++)
		{
			out << "| ";
			for (int j = 0; j < sys.variables(); j++)
			{
				out << sys.matrix_.getElem(i, j) << ' ';
			}
			out << " | ";
			out << sys.vector_[i] << std::endl;
		}
		return out;
	}

	std::istream& operator>>(std::istream& in, LinearSystem& sys)
	{
		in >> sys.matrix_ >> sys.vector_;
		return in;
	}
}
