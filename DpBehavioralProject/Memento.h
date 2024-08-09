#pragma once
#include <iostream>
#include <vector>

// Memento
class IMemento
{
public:

};

class PlayerState;

// Originator
class Player
{
	int points;
	int level;

	// others data
public:
	Player() : points{}, level{ 1 }
	{
		srand(time(nullptr));
	}

	void Play()
	{
		int p = 1 + rand() % 5;
		points += p;

		if (points / 10 >= level)
			level++;

		std::cout << "current player state: points = " << points
			<< ", level = " << level << "\n";
	}

	PlayerState* Save();
	void Load(PlayerState* state);
};

// Memento
class PlayerState
{
	int points;
	int level;
public:
	PlayerState(int points, int level) : points{ points }, level{ level } {}
	int Points() { return points; }
	int Level() { return level; }
};

PlayerState* Player::Save()
{
	std::cout << "save player state: points = " << points
		<< ", level = " << level << "\n";
	return new PlayerState(points, level);
}

void Player::Load(PlayerState* state)
{
	this->points = state->Points();
	this->level = state->Level();
	std::cout << "load player state: points = " << points
		<< ", level = " << level << "\n";
}

class GameHistory
{
	std::vector<PlayerState*> history;
public:
	void Add(PlayerState* state)
	{
		history.push_back(state);
	}

	PlayerState* Remove(int index = -1)
	{
		if (index == -1)
			index = history.size() - 1;

		PlayerState* state = history[index];
		history.erase(history.begin() + index);
		return state;
	}
};