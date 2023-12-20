#pragma once
#include "InputManager.h"
#include "Entity.h"


using namespace std;

class Player : public Entity
{
	ProgessBar hunger;
	ProgessBar thirst;

public:
	Player();
	Player(const float _maxHunger, const float _maxThirst,const float _maxHp);

public:

	float GetHunger() const 
	{
		return hunger.currentValue;
	}

	float GetThirst() const 
	{
		return thirst.currentValue;
	}
private:
	void UpdateVital(const float _amount, ProgessBar& _value);

public:
	void UpdateVital(const VitalType& _type, const float _amount) override;
	virtual void DisplayStatistics(const bool _top = true, const bool _bottom = true) const override;
};

