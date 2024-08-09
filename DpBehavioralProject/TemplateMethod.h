#pragma once
#include <iostream>

// TemplateMethod
class Education
{
public:
	virtual void TemplateMethod()
	{
		Enter();
		Study();
		Examen();
		GetDocument();
	}

	virtual void Enter() = 0;
	virtual void Study() = 0;
	virtual void Examen() = 0;
	virtual void GetDocument() = 0;
};

class School : public Education
{
public:
	void Enter() override 
	{
		std::cout << "enter to first class\n";
	}

	void Study() override
	{
		std::cout << "study in school\n";
		std::cout << "homeworks in house\n";
	}

	void Examen() override
	{
		std::cout << "ege\n";
	}

	void GetDocument() override
	{
		std::cout << "get attestat\n";
	}
};

class Universitet : public Education
{
public:
	void Enter() override
	{
		std::cout << "inputs examen\n";
		std::cout << "enter to first course\n";
	}

	void Study() override
	{
		std::cout << "study in universitet\n";
		std::cout << "practic\n";
	}

	void Examen() override
	{
		std::cout << "output examen\n";
	}

	void GetDocument() override
	{
		std::cout << "get diplome\n";
	}
};
