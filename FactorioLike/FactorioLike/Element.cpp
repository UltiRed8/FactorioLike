#include "Element.h"

Element::Element(const char _sign)
{
	sign = _sign;
}

Location& operator+=(Location& _newLocation, const Location& _currentLocation)
{
	_newLocation.posX = _currentLocation.posX;
	_newLocation.posY = _currentLocation.posY;

	return _newLocation;
}
