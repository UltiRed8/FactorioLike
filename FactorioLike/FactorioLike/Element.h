#pragma once

struct Location
{
	int _posX = 0;
	int _posY = 0;
};

Location& operator += (Location& _newLocation, const Location& _currentLocation);

class Element
{
protected:
	Location location;

public:
	void SetLocation(const Location& _newLocation)
	{
		location = _newLocation;
	}

public:
	Element();
};

