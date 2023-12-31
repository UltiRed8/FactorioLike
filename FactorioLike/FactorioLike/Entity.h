#pragma once

#include "Element.h"
#include "GameManager.h"
#include "ProgressBar.h"

#include <iostream>

using namespace std;

enum VitalType
{
	VT_NONE, VT_HP, VT_HUNGER, VT_THRIST
};

class Entity : public Element
{
protected:
	ProgessBar hp;

public:
	Entity(const float _maxHp, const string _sign);

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
	bool Move(const Location& _deltaLoc);
	virtual void UpdateVital(const VitalType& _type, const float _amount) = 0;
	virtual void DisplayStatistics(const bool _top = true, const bool _bottom = true) const;
};

