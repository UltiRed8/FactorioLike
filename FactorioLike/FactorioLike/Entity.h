#pragma once

#include "Element.h"
#include "Macros.h"
#include "GameManager.h"
#include <iostream>

using namespace std;

enum VitalType
{
	VT_NONE, VT_HP, VT_HUNGER, VT_THRIST
};

struct ProgessBar
{
	float maxValue = 100;
	float currentValue = 75;

public:
	void Display(const string& _title, const wchar_t& _filledChar, const int _arrowLenght, const int _barLenght) const {
		const int _progress = static_cast<const int>(currentValue / maxValue * _barLenght);
		cout << "#> " << _title;
		for (int _i = 0; _i < _arrowLenght; _i++) cout << "-";
		cout << "> ";
		for (int _i = 0; _i < _barLenght; _i++) {
			if (_i <= _progress) {
				SPECIALCHAR(_filledChar);
			} else cout << "-";
		}
		cout << " #" << endl;
	}
};

class Entity : public Element
{
protected:
	ProgessBar hp;

public:
	Entity(const float _maxHp, const char _sign);

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
	virtual void DisplayStatistics(const bool _top = true, const bool _bottom = true) const;
};

