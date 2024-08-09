#pragma once
#include <iostream>
//enum WaterState
//{
//	SOLID,
//	LIQUID,
//	GAS
//};

class Water;

class IWaterState
{
public:
	virtual void Heat(Water* water) = 0;
	virtual void Frost(Water* water) = 0;
};

//Context
class Water
{
	IWaterState* state;
public:
	IWaterState*& State() { return state; }

	Water(IWaterState* state) : state{ state } {}

	void Heat()
	{
		state->Heat(this);
	}

	void Frost()
	{
		state->Frost(this);
	}
};

class SolidState;
class LiquidState;
class GasState;

class SolidState : public IWaterState
{
public:
	void Heat(Water* water) override;
	void Frost(Water* water) override;
};

class LiquidState : public IWaterState
{
public:
	void Heat(Water* water) override;
	void Frost(Water* water) override;
};

class GasState : public IWaterState
{
public:
	void Heat(Water* water) override;
	void Frost(Water* water) override;
};


//
void SolidState::Heat(Water* water)
{
	std::cout << "ice to water\n";
	water->State() = new LiquidState();
}
void SolidState::Frost(Water* water)
{
	std::cout << "ice to ice\n";
}

//
void LiquidState::Heat(Water* water)
{
	std::cout << "water to gas\n";
	water->State() = new GasState();
}
void LiquidState::Frost(Water* water)
{
	std::cout << "water to ice\n";
	water->State() = new SolidState();
}

//
void GasState::Heat(Water* water)
{
	std::cout << "gas to gas\n";
}
void GasState::Frost(Water* water)
{
	std::cout << "gas to water\n";
	water->State() = new LiquidState();
}