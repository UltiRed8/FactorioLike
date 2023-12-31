#include "GameManager.h"
#include "Player.h"

GameManager::GameManager()
{
	lastUpdatedTick = uint64_t();
	player = new Player();
	map = new Map(24, player);
	ticksAmount = 20;
	message = new GameMessage("Bienvenue sur le jeu FactorioLike !", ticksAmount, 5);
}

GameManager::~GameManager()
{
	delete map;
	if (message) delete message;
}

void GameManager::Loop()
{
	do
	{
		if (Interval()) Draw();
		InputManager::GetInstance()->Tick();
	} while (true);
}

void GameManager::Draw()
{
	system("CLS");
	if (!player->IsInInventory()) map->Display();
	if (message)
	{
		string _messageText = message->GetDisplayMessage();
		if (_messageText == "")
		{
			delete message;
			message = nullptr;
		}
		else cout << endl << _messageText << endl;
	}
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