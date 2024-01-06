#include "GameManager.h"
#include "Player.h"

GameManager::GameManager()
{
	lastUpdatedTick = uint64_t();
	message = new GameMessage("Bienvenue sur le jeu FactorioLike !", ticksAmount, 5);
	saveName = "";
	ticksAmount = 20;
	player = nullptr;
	map = nullptr;
	mapSize = 24;
	wantsToQuit = false;
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
	} while (!wantsToQuit);
}

void GameManager::Draw()
{
	if (player->IsInGame())
	{
		system("CLS");
		map->Display();
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
}

void GameManager::Start()
{
	LoadGame();
	Loop();
}

void GameManager::LoadGame()
{
	player = new Player();
	map = new Map(mapSize, player);
	try
	{
		FileManager::GetInstance()->LoadGame(saveName, map);
	}
	catch (const exception _error)
	{
		cerr << _error.what() << endl;
		//system("PAUSE") On ne veux pas mettre pause, si il y as une erreur => nouvelle partie
		map->Generate();
	}
}

void GameManager::SaveGame()
{
	FileManager::GetInstance()->SaveGame(saveName, map);
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