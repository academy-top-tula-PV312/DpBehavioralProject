#pragma once

template <typename T>
class IIterator
{
public:
	virtual void Set() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual T Current() = 0;
};

class Matrix
{
	int rows;
	int columns;
	int** matrix;
public:
	int Rows() { return rows; }
	int Columns() { return columns; }

	Matrix(int rows, int columns) : rows{ rows }, columns{ columns }
	{
		matrix = new int*[rows];
		for (int i{}; i < rows; i++)
			matrix[i] = new int[columns] {};
	}

	~Matrix()
	{
		for (int i{}; i < rows; i++)
			delete[] matrix[i];
		delete[] matrix;
	}

	int& operator()(int row, int column)
	{
		return matrix[row][column];
	}

	IIterator<int>* HMatrixIterator();

	IIterator<int>* VMatrixIterator();
};

class HorizontalMatrixIterator : public IIterator<int>
{
	Matrix* matrix;
	int row;
	int column;
public:
	HorizontalMatrixIterator(Matrix* matrix)
		: matrix{ matrix }, row{}, column{} {}

	void Set() override 
	{
		row = 0;
		column = 0;
	}

	void Next() override 
	{
		if (column < matrix->Columns() - 1)
			column++;
		else if (row < matrix->Rows() - 1)
		{
			row++;
			column = 0;
		}
		else
		{
			column++;
		}
	}

	bool IsDone() override
	{
		return row == matrix->Rows() - 1 && column == matrix->Columns();
	}

	int Current() override 
	{
		return (*matrix)(row, column);
	}
};

IIterator<int>* Matrix::HMatrixIterator()
{
	return new HorizontalMatrixIterator(this);
}


class VerticalMatrixIterator : public IIterator<int>
{
	Matrix* matrix;
	int row;
	int column;
public:
	VerticalMatrixIterator(Matrix* matrix)
		: matrix{ matrix }, row{}, column{} {}

	void Set() override 
	{
		row = 0;
		column = 0;
	}

	void Next() override 
	{
		if (row < matrix->Rows() - 1)
			row++;
		else if (column < matrix->Columns() - 1)
		{
			column++;
			row = 0;
		}
		else
			row++;
	}

	bool IsDone() override 
	{
		return row == matrix->Rows() && column == matrix->Columns() - 1;
	}

	int Current() override 
	{
		return (*matrix)(row, column);
	}
};

IIterator<int>* Matrix::VMatrixIterator()
{
	return new VerticalMatrixIterator(this);
}
