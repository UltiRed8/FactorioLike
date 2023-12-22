#include "GameManager.h"

GameManager::GameManager()
{
	lastUpdatedTick = uint64_t();
	map = new Map(25);
	ticksAmount = 1; // TODO changer en version finale
}

GameManager::~GameManager()
{
	delete map;
}

void GameManager::Loop()
{
	do {
		if (Interval()) Tick();
	} while (true);
}

void GameManager::Tick()
{
	system("CLS");
	map->Display();
}

void GameManager::Start()
{
	Loop();
}

bool GameManager::Interval()
{
	uint64_t _currentTime = duration_cast<chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
	if (_currentTime - lastUpdatedTick >= 1000/ticksAmount)
	{
		lastUpdatedTick = _currentTime;
		return true;
	}
	return false;
}