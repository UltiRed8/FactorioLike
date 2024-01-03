#pragma once

#include "Singleton.h"
#include "Map.h"
#include "InputManager.h"

#include <chrono>

class Player;

using namespace std::chrono;

struct GameMessage {
	string message = "";
	int displayTicks = 0;

public:
	GameMessage(const string& _message, const int _ticksPerSeconds, const int _amountOfSecondsToShow)
	{
		message = _message;
		displayTicks = _ticksPerSeconds * _amountOfSecondsToShow;
	}

public:
	string GetDisplayMessage()
	{
		if (displayTicks > 0) displayTicks--;
		if (displayTicks == 0) message = "";
		return message;
	}
};

class GameManager : public Singleton<GameManager>
{
	uint64_t lastUpdatedTick;
	Map* map;
	int ticksAmount;
	Player* player;
	GameMessage* message;

public:
	int GetTicksPerSeconds() const {
		return ticksAmount;
	}
	Map* GetMap() const
	{
		return map;
	}
	void SetGameMessage(const string& _message, const int _seconds)
	{
		if (message) delete message;
		message = new GameMessage(_message, ticksAmount, _seconds);
	}

public:
	GameManager();
	~GameManager();

private:
	void Loop();
	bool Interval();
	void Draw();

public:
	void Start();
};