#pragma once

struct Location {
	int posX = 0;
	int posY = 0;

	void operator += (const Location& _currentLocation) {
		posX += _currentLocation.posX;
		posY += _currentLocation.posY;
	}
};