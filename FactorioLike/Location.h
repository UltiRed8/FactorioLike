#pragma once

#include "Macros.h"

struct Location {
	int posX = 0;
	int posY = 0;

	void operator += (const Location& _currentLocation) {
		posX += _currentLocation.posX;
		posY += _currentLocation.posY;
	}

	void Random(const int _min, const int _max) {
		posX = RandomInRange(_max, _min);
		posY = RandomInRange(_max, _min);
	}
};