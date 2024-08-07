#pragma once
#include <vector>

class Vector;

class IStrategy
{
public:
	//virtual void SortStrategy(Vector&) = 0;
	virtual void operator()(Vector&) = 0;
};

class Vector
{
	std::vector<int> v;
	IStrategy* sortStrategy;
public:
	Vector(int size) : sortStrategy{ nullptr }
	{
		v.resize(size);
	}
	
	std::vector<int>& V() { return v; }
	
	void SetStrategy(IStrategy* sortStrategy)
	{
		this->sortStrategy = sortStrategy;
	}

	void Sort()
	{
		(*sortStrategy)(*this);
	}
};

class SelectSortStrategy : public IStrategy
{
public:
	//void SortStrategy(Vector& vect) override
	void operator()(Vector& vect) override
	{
		for (int i{}; i < vect.V().size(); i++)
		{
			int imin = i;
			for (int j{ i + 1 }; j < vect.V().size(); j++)
				if (vect.V()[j] < vect.V()[imin])
					imin = j;
			int temp = vect.V()[i];
			vect.V()[i] = vect.V()[imin];
			vect.V()[imin] = temp;
		}
	}
};

class BubbleSortStrategy : public IStrategy
{
public:
	//void SortStrategy(Vector& vect) override
	void operator()(Vector& vect) override
	{
		for (int i{}; i < vect.V().size(); i++)
			for (int j = vect.V().size() - 1; j > i; j--)
				if (vect.V()[j] < vect.V()[j - 1])
				{
					int temp = vect.V()[j];
					vect.V()[j] = vect.V()[j - 1];
					vect.V()[j - 1] = temp;
				}

	}
};



