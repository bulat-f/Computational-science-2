#ifndef LINEAR_SYSTEM_H_
#define LINEAR_SISTEM_H_

#include <iostream>
#include "matrix.h"
#include "vector.h"

namespace KFU
{
	class LinearSystem
	{
		public:
			LinearSystem();
			LinearSystem(int);
			LinearSystem(int, int);
			LinearSystem(const Matrix<double>&, const Vector<double>&);
			LinearSystem(const LinearSystem&);

			int equations() const;
			int variables() const;

			int get_jacobi_counter() const;
			int get_seidel_counter() const;
			int get_relaxation_counter() const;

			void swap_lines(int, int);

			Vector<double> solve();
			Vector<double> true_solution();
			Vector<double> jacobi(double = 1e-5);
			Vector<double> seidel(double = 1e-5);
			Vector<double> relaxation(double = 1e-5, double = 1.5);
		private:
			Vector<double> vector_;
			Matrix<double> matrix_;

			int jacobi_counter, seidel_counter, relaxation_counter;

			Vector<double> next_jacobi(Vector<double>&);
			Vector<double> next_seidel(Vector<double>&);
			Vector<double> next_relaxation(Vector<double>&, const double);

			friend std::ostream& operator<<(std::ostream&, LinearSystem&);
			friend std::istream& operator>>(std::istream&, LinearSystem&);
	};
}

#endif
