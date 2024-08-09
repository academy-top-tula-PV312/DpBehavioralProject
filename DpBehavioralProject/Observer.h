#pragma once
#include <iostream>
#include <vector>

template <typename ObservableData>
class IObserver
{
public:
	virtual void EventHandler(ObservableData data) = 0;
};

template <typename ObservableData>
class IObservable
{
protected:
	std::vector<IObserver<ObservableData>*> subscribers;
public:
	virtual void AddObserver(IObserver<ObservableData>* subscriber) = 0;
	virtual void RemoveObserver(IObserver<ObservableData>* subscriber) = 0;
	virtual void NotifyObservers() = 0;
};

struct MarketInfo
{
	int usd{};
	int euro{};
};

// Observable - Publisher
class Market : public IObservable<MarketInfo>
{
	MarketInfo info;
public:
	Market() { srand(time(nullptr)); }

	void AddObserver(IObserver<MarketInfo>* subscriber) override
	{
		subscribers.push_back(subscriber);
	}

	void RemoveObserver(IObserver<MarketInfo>* subscriber) override
	{
		auto it = std::find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end())
			subscribers.erase(it);
	}

	void NotifyObservers() override
	{
		for (auto subscriber : subscribers)
			subscriber->EventHandler(info);
	}

	void Bidding()
	{
		info.usd = 80 + rand() % 20;
		info.euro = 90 + rand() % 25;

		std::cout << "usd = " << info.usd << "\n";
		std::cout << "euro = " << info.euro << "\n";

		NotifyObservers();
	}
};

class Broker : public IObserver<MarketInfo>
{
	std::string name;
	IObservable<MarketInfo>* publisher;
public:
	Broker(std::string name, IObservable<MarketInfo>* publisher)
		: name{ name }, publisher{ publisher } 
	{
		publisher->AddObserver(this);
	}

	std::string Name() { return name; }

	void EventHandler(MarketInfo data) override
	{
		if (data.usd < 90)
			std::cout << "byed usd at " << data.usd << "\n";
		else
			std::cout << "saled usd at " << data.usd << "\n";

		if (data.euro < 95)
			std::cout << "byed euro at " << data.euro << "\n";
		else
			std::cout << "saled euro at " << data.euro << "\n";
	}

	void StopWork()
	{
		publisher->RemoveObserver(this);
	}
};

class Bank : public IObserver<MarketInfo>
{
	std::string name;
	IObservable<MarketInfo>* publisher;
public:
	Bank(std::string name, IObservable<MarketInfo>* publisher = nullptr)
		: name{ name }, publisher{ publisher }
	{
		if(publisher)
			publisher->AddObserver(this);
	}

	std::string Name() { return name; }

	void EventHandler(MarketInfo data) override
	{
			std::cout << "Bank " << name << " saled usd at " << data.usd + 10 << "\n";
			std::cout << "Bank " << name << " saled euro at " << data.euro + 10 << "\n";
	}

	void StopWork()
	{
		publisher->RemoveObserver(this);
	}
};