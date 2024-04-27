#include "Matrices.h"
namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols) {
		a.resize(_rows);
		for (int i = 0; i < _rows; i++) {
			a[i].resize(_cols);
			for (int j = 0; j < _cols; j++) {
				a[i][j] = 0;
			}
		}
		rows = _rows;
		cols = _cols;
	}

	Matrix operator+(const Matrix& a, const Matrix& b) {
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), a.getCols());
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				c(i, j) = a(i, j) + b(i, j);
			}
		}
		return c;
	}

	Matrix operator*(const Matrix& a, const Matrix& b) {
		if (a.getCols() != b.getRows()) {
			throw runtime_error("Error: dimensions must agree");
		}
		Matrix c(a.getRows(), b.getCols());
		for (int k = 0; k < b.getCols(); k++) {
			for (int i = 0; i < a.getRows(); i++) {
				double sum = 0;
				for (int j = 0; j < a.getCols(); j++) {
					sum += a(i, j) * b(j, k);
				}
				c(i, k) = sum;
			}
		}
		return c;
	}

	bool operator==(const Matrix& a, const Matrix& b) {
		bool status = false;
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			return false;
		}
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if (abs(a(i, j) - b(i, j)) < 0.001) {
					status = true;
				}
				else {
					return false;
				}
			}
		}
		return status;
	}

	bool operator!=(const Matrix& a, const Matrix& b) {
		bool status = true;
		if (a.getRows() != b.getRows() || a.getCols() != b.getCols()) {
			return true;
		}
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				if (abs(a(i, j) - b(i, j)) < 0.001) {
					status = false;
				}
				else {
					return true;
				}
			}
		}
		return status;
	}

	ostream& operator<<(ostream& os, const Matrix& a) {
		for (int i = 0; i < a.getRows(); i++) {
			for (int j = 0; j < a.getCols(); j++) {
				os << setw(10) << a(i, j);
			}
			os << "\n";
		}
		os << "\n";
		return os;
	}

	RotationMatrix::RotationMatrix(double theta)
		: Matrix(2,2)
	{
		a[0][0] = cos(theta);
		a[0][1] = -sin(theta);
		a[1][0] = sin(theta);
		a[1][1] = cos(theta);
	}

	ScalingMatrix::ScalingMatrix(double scale)
		: Matrix(2,2)
	{
		a[0][0] = scale;
		a[0][1] = 0;
		a[1][0] = scale;
		a[1][1] = 0;
	}

	TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols)
		: Matrix(2, nCols)
	{
		for (int j = 0; j < nCols; j++)
		{
			a[0][j] = xShift;
			a[1][j] = yShift;
		}
	}
}