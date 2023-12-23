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
	float ticksAmount;
	Player* player;

public:
	Map* GetMap() const
	{
		return map;
	}

public:
	GameManager();
	~GameManager();

private:
	void Loop();
	void Tick();
	bool Interval();

public:
	void Start();
};