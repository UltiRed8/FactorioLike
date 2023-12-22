#pragma once
#include "Macros.h"

struct Location
{
	int posX = 0;
	int posY = 0;

public:

	void Random(const int _min, const int _max) {
		posX = RandomInRange(_max, _min);
		posY = RandomInRange(_max, _min);
	}
};

Location& operator += (Location& _newLocation, const Location& _currentLocation);

class Element
{
protected:
	Location location;
	char sign;

public:
	void SetLocation(const Location& _newLocation)
	{
		location = _newLocation;
	}

public:
	Element(const char _sign);
};

