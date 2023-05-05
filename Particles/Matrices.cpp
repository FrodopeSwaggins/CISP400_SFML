#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
		rows = _rows;
		cols = _cols;

		a.resize(rows, vector<double>(cols));
	}

	ostream& operator<<(ostream& os, const Matrix& a)
	{
		for (size_t i = 0; i < a.getRows(); i++) 
		{
			os << "\n";
			for (size_t j = 0; j < a.getCols(); j++) 
			{
				os << setw(10) << a(i, j) << " ";
			}
			os << "\n";
		}
		return os;
	}

	Matrix operator+(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getCols() || a.getRows() != b.getRows()) 
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); i++) 
		{
			for (int j = 0; j < a.getCols(); j++) 
			{
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b)
	{
		if (a.getCols() != b.getRows())
		{
			throw runtime_error("Error: dimensions must agree");
		}

		Matrix c(a.getRows(), b.getCols());
		
		for (int i = 0; i < a.getRows(); i++) 
		{
			for (int k = 0; k < b.getCols(); k++)
			{
				for (int j = 0; j < a.getCols(); j++)
				{
					c(i, k) += a(i, j) * b(j, k);
				}
			}
		}
		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < b.getCols(); j++) 
			{
				if (fabs(a(i, j) - b(i, j)) < 0.001) 
				{
					return true;
				}
			}
		}
		return false;
	}

	bool operator!=(const Matrix& a, const Matrix& b)
	{
		for (int i = 0; i < a.getRows(); i++)
		{
			for (int j = 0; j < b.getCols(); j++)
			{
				if (fabs(a(i, j) - b(i, j)) > 0.001)
				{
					return true;
				}
			}
		}
		return false;
	}

	RotationMatrix::RotationMatrix(double theta) 
	{
		
	}

}