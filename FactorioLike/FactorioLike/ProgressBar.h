#pragma once

#include "Macros.h"
#include "Colors.h"

#include <iostream>

using namespace std;

struct ProgessBar {
	float maxValue = 100;
	float currentValue = 100;

public:
	void Display(const string& _title, const string& _color, const wchar_t& _filledChar, const int _arrowLenght, const int _barLenght) const {
		const int _progress = static_cast<const int>(currentValue / maxValue * _barLenght);
		cout << "#> " << _color << _title;
		for (int _i = 0; _i < _arrowLenght; _i++) cout << "-";
		cout << "> ";
		for (int _i = 0; _i < _barLenght; _i++) {
			if (_i <= _progress) {
				SPECIALCHAR(_filledChar);
			} else cout << "-";
		}
		cout << COLORRESET << " #" << endl;
	}
};