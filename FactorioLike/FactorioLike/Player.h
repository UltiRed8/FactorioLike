#pragma once

#include "InputManager.h"
#include "Entity.h"
#include "Inventory.h"
#include "Menu.h"

using namespace std;

enum PlayerState
{
	PS_GAME, PS_INVENTORY, PS_BUILDING, PS_ESCAPE
};

class Player : public Entity
{
	Inventory inventory;
	PlayerState state;
	ProgessBar hunger;
	ProgessBar thirst;
	Menu* currentMenu;

public:
	Player();
	Player(const float _maxHunger, const float _maxThirst,const float _maxHp);
	~Player();

public:
	float GetHunger() const
	{
		return hunger.currentValue;
	}
	float GetThirst() const
	{
		return thirst.currentValue;
	}
	bool IsInInventory() const
	{
		return state == PS_INVENTORY;
	}
	bool IsInGame() const
	{
		return state == PS_GAME;
	}

private:
	void UpdateVital(const float _amount, ProgessBar& _value);
	void InitKeybinds();
	void Direction(const Location& _direction);
	void ToggleInventory();
	void BuildMenu();
	void EscapeMenu();
	void DeleteMenu();
	void CloseMenu();

public:
	void UpdateVital(const VitalType& _type, const float _amount) override;
	virtual void DisplayStatistics(const bool _top = true, const bool _bottom = true) const override;
};