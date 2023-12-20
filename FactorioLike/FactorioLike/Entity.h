#pragma once
#include "GameManager.h"
#include "Element.h"

enum VitalType
{
	VT_NONE, VT_HP, VT_HUNGER, VT_THRIST
};

struct ProgessBar
{
	float maxValue = 100;
	float currentValue = 100;
};

class Entity : public Element
{
protected:
	ProgessBar hp;

public:
	Entity();
	Entity(const float _maxHp);

public:
	float GetCurrentHp()
	{
		return hp.currentValue;
	}

	float GetMaxHp()
	{
		return hp.maxValue;
	}

public:
	void Move(const Location& _deltaLoc);
	virtual void UpdateVital(const VitalType& _type, const float _amount) = 0;
};

