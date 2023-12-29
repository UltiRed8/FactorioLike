#pragma once

#include "Singleton.h"
#include "Map.h"
#include "InputManager.h"

#include <chrono>

class Player;

using namespace std::chrono;

class GameManager : public Singleton<GameManager>
{
	uint64_t lastUpdatedTick;
	Map* map;
	int ticksAmount;
	Player* player;

public:
	int GetTicksPerSeconds() const {
		return ticksAmount;
	}
	Map* GetMap() const
	{
		return map;
	}

public:
	GameManager();
	~GameManager();

private:
	void Loop();
	bool Interval();

public:
	void Start();
};