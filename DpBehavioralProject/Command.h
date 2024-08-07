#pragma once
#include <iostream>
#include <stack>

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual bool CanExecute() = 0;
};

class Television
{
	bool isPower;
	int soundVolume;
	const int maxVolume{ 5 };
public:
	Television()
		: isPower{ false },
		soundVolume{} {}

	void PowerOn()
	{
		std::cout << "Tv power on\n";
		isPower = true;
	}

	void PowerOff()
	{
		std::cout << "Tv power off\n";
		isPower = false;
	}

	void SoundUp()
	{
		if (soundVolume < maxVolume)
			soundVolume++;

		std::cout << "Tv sound up, volume = " << soundVolume << "\n";
	}

	void SoundDown()
	{
		if (soundVolume > 0)
			soundVolume--;

		std::cout << "Tv sound down, volume = " << soundVolume << "\n";
	}

	bool& IsPower() { return isPower; }
	int& SoundVolume() { return soundVolume; }
	int MaxVolume() { return maxVolume; }
};


class TvOnCommand : public ICommand
{
	Television* tv;
public:
	TvOnCommand(Television* tv) : tv{ tv } {}

	void Execute() override 
	{
		tv->PowerOn();
	}

	void Undo() override 
	{
		tv->PowerOff();
	}

	bool CanExecute() override 
	{
		return !tv->IsPower();
	}
};

class TvOffCommand : public ICommand
{
	Television* tv;
public:
	TvOffCommand(Television* tv) : tv{ tv } {}

	void Execute() override
	{
		tv->PowerOff();
	}

	void Undo() override
	{
		tv->PowerOn();
	}

	bool CanExecute() override
	{
		return tv->IsPower();
	}
};


class TvSoundUpCommand : public ICommand
{
	Television* tv;
public:
	TvSoundUpCommand(Television* tv) : tv{ tv } {}

	void Execute() override
	{
		tv->SoundUp();
	}

	void Undo() override
	{
		tv->SoundDown();
	}

	bool CanExecute() override
	{
		return tv->IsPower() && tv->SoundVolume() < tv->MaxVolume();
	}
};

class TvSoundDownCommand : public ICommand
{
	Television* tv;
public:
	TvSoundDownCommand(Television* tv) : tv{ tv } {}

	void Execute() override
	{
		tv->SoundDown();
	}

	void Undo() override
	{
		tv->SoundUp();
	}

	bool CanExecute() override
	{
		return tv->IsPower() && tv->SoundVolume() > 0;
	}
};

class Controller
{
	ICommand* power;
	ICommand* soundPlus;
	ICommand* soundMinus;

	bool powerAction;

	std::stack<ICommand*> history;

public:
	Controller(ICommand* power,
		ICommand* soundPlus,
		ICommand* soundMinus)
		: power{ power },
		soundPlus{ soundPlus },
		soundMinus{ soundMinus },
		powerAction{ false } {}

	void PowerButton()
	{
		if (!powerAction)
			power->Execute();
		else
			power->Undo();
		powerAction = !powerAction;
	}

	void PlusButton()
	{
		if (soundPlus->CanExecute())
		{
			soundPlus->Execute();
			history.push(soundPlus);
		}
	}

	void MinusButton()
	{
		if (soundMinus->CanExecute())
		{
			soundMinus->Execute();
			history.push(soundMinus);
		}
	}

	void UndoButton()
	{
		if (history.size() > 0)
		{
			history.top()->Undo();
			history.pop();
		}
	}

};