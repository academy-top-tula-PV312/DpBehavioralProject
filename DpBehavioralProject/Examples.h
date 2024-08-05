#pragma once
#include <iostream>
#include "Iterator.h"

class Examples
{
public:
	static void Iterator()
	{
        Matrix matrix(4, 5);

        for (int i{}; i < matrix.Rows(); i++)
            for (int j{}; j < matrix.Columns(); j++)
                matrix(i, j) = (i + 1) * 10 + (j + 1);

        for (int i{}; i < matrix.Rows(); i++)
        {
            for (int j{}; j < matrix.Columns(); j++)
                std::cout << matrix(i, j) << " ";
            std::cout << "\n";
        }

        auto hi = matrix.HMatrixIterator();

        for (hi->Set(); !hi->IsDone(); hi->Next())
            std::cout << hi->Current() << " ";

        std::cout << "\n";

        auto vi = matrix.VMatrixIterator();
        for (vi->Set(); !vi->IsDone(); vi->Next())
            std::cout << vi->Current() << " ";

        std::cout << "\n";
	}
};

