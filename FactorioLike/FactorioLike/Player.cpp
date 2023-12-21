#include "Player.h"

Player::Player() : Entity() 
{
	inventory.AddItem(new Item("Heavy"), 1);
	inventory.AddItem(new Item("epee"), 52);
	inventory.AddItem(new Item("water"), 5);
	inventory.AddItem(new Item("stone"), 100);
	inventory.AddItem(new Item("pickaxe"), 86);
	inventory.AddItem(new Item("hache"), 18);
	
	InputManager& _manager= InputManager::GetInstance();
	_manager.AddKeybind({ 'z', 72 }, [&]() { Move({ -1, 0 }); });
	_manager.AddKeybind({ 'q', 75 }, [&]() { Move({ 0, -1 }); });
	_manager.AddKeybind({ 's', 80 }, [&]() { Move({ 0, 1 }); });
	_manager.AddKeybind({ 'd', 77 }, [&]() { Move({ 1, 0 }); });
	_manager.AddKeybind({ 'e' }, [&]() { inventory.DisplayInventory(); });
}

Player::Player(const float _maxHunger, const float _maxThirst, const float _maxHp) : Entity(_maxHp)
{
	hunger = { _maxHunger,_maxHunger };
	thirst = { _maxThirst,_maxThirst };
}

void Player::UpdateVital(const VitalType& _type, const float _amount)
{
	switch (_type)
	{
	case VT_NONE:
		break;
	case VT_HP:
		UpdateVital(_amount, hp);
		break;
	case VT_HUNGER:
		UpdateVital(_amount, hunger);
		break;
	case VT_THRIST:
		UpdateVital(_amount, thirst);
		break;
	default:
		break;
	}
}

void Player::DisplayStatistics(const bool _top, const bool _bottom) const {
	if (_top) cout << "##################################" << endl;
	hunger.Display("HUNGER", '@', 1, 20);
	thirst.Display("THIRST", '@', 1, 20);
	Entity::DisplayStatistics(false, _bottom);
}

void Player::UpdateVital(const float _amount,ProgessBar& _value)
{
	float currentValue = _value.currentValue;
	float maxValue = _value.maxValue;
	currentValue = currentValue + _amount >= maxValue ? maxValue : currentValue + _amount;
	_value.currentValue = currentValue;
}
