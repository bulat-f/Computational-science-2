#ifndef LINEAR_SYSTEM_H_
#define LINEAR_SISTEM_H_

#include <iostream>
#include "matrix.h"
#include "vector.h"
#include "complex.h"

namespace KFU
{
	class LinearSystem
	{
		public:
			LinearSystem();
			LinearSystem(int, int);
			LinearSystem(const Matrix<double>&, const Vector<double>&);
			LinearSystem(const LinearSystem&);

			int equations() const;
			int variables() const;

			void swap_lines(int, int);

			Vector<double> solve();
			Vector<double> solve2(double = 1e-5);
		private:
			Vector<double> vector_;
			Matrix<double> matrix_;
			friend std::ostream& operator<<(std::ostream&, LinearSystem&);
			friend std::istream& operator>>(std::istream&, LinearSystem&);
	};
}

#endif
