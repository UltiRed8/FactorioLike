#include "Element.h"

Element::Element() {}

Location& operator+=(Location& _newLocation, const Location& _currentLocation)
{
	_newLocation._posX = _currentLocation._posX;
	_newLocation._posY = _currentLocation._posY;

	return _newLocation;
}
