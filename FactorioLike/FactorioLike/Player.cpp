#include "Player.h"

Player::Player() : Entity() 
{
	InputManager _manager= InputManager::GetInstance();
	_manager.AddKeybind({ 'z' }, [&]() {Move({1,0}); });
	_manager.AddKeybind({ 'q' }, [&]() {Move({0,-1}); });
	_manager.AddKeybind({ 's' }, [&]() {Move({0,1}); });
	_manager.AddKeybind({ 'd' }, [&]() {Move({-1,0}); });
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

void Player::UpdateVital(const float _amount,ProgessBar& _value)
{
	float currentValue = _value.currentValue;
	float maxValue = _value.maxValue;
	currentValue = currentValue + _amount >= maxValue ? maxValue : currentValue + _amount;
	_value.currentValue = currentValue;
}
