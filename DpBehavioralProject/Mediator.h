#pragma once
#include <iostream>

enum CollegueType
{
	Customer,
	Developer,
	Tester
};

class Collegue;

class IMediator
{
public:
	virtual void Send(std::string message, Collegue* collegue) = 0;
};

class Collegue
{
	IMediator* mediator;
	CollegueType type;

public:
	Collegue(IMediator* mediator, CollegueType type)
		: mediator{ mediator }, type{ type } {}

	virtual void Send(std::string message)
	{
		mediator->Send(message, this);
	}

	CollegueType& Type() { return type; }

	virtual void Notify(std::string message) = 0;
};

class CustomerCollegue : public Collegue
{
public:
	CustomerCollegue(IMediator* mediator)
		: Collegue(mediator, CollegueType::Customer) {}
	void Notify(std::string message) override
	{
		std::cout << "Message for customer " << message << "\n";
	}
};

class DeveloperCollegue : public Collegue
{
public:
	DeveloperCollegue(IMediator* mediator)
		: Collegue(mediator, CollegueType::Developer) {}
	void Notify(std::string message) override
	{
		std::cout << "Message for developer " << message << "\n";
	}
};

class TesterCollegue : public Collegue
{
public:
	TesterCollegue(IMediator* mediator)
		: Collegue(mediator, CollegueType::Tester) {}
	void Notify(std::string message) override
	{
		std::cout << "Message for tester " << message << "\n";
	}
};

class ProjectManager : public IMediator
{
	Collegue* customer;
	Collegue* developer;
	Collegue* tester;
public:
	Collegue*& Customer() { return customer; }
	Collegue*& Developer() { return developer; }
	Collegue*& Tester() { return tester; }
	
	void Send(std::string message, Collegue* collegue)
	{
		switch (collegue->Type())
		{
		case CollegueType::Customer:
			developer->Notify(message);
			break;
		case CollegueType::Developer:
			tester->Notify(message);
			break;
		case CollegueType::Tester:
			customer->Notify(message);
			break;
		default:
			break;
		}
	}
};

