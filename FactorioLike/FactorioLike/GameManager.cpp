#include "GameManager.h"
#include "Player.h"

GameManager::GameManager()
{
	lastUpdatedTick = uint64_t();
	player = new Player();
	map = new Map(24, player); // TODO changer en version finale
	ticksAmount = 20; // TODO changer en version finale
}

GameManager::~GameManager()
{
	delete map;
}

void GameManager::Loop()
{
	do
	{
		if (Interval() && !player->IsInInventory()) map->Display();
		InputManager::GetInstance()->Tick();
	} while (true);
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