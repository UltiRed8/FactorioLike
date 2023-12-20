#pragma once

#include "Singleton.h"
#include "Map.h"

#include <chrono>
#include "InputManager.h"

using namespace std::chrono;

class GameManager : public Singleton<GameManager>
{
	uint64_t lastUpdatedTick;
	Map* map;
	float ticksAmount;

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