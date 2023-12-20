#include "Element.h"

Element::Element() {}

Location& operator+=(Location& _newLocation, const Location& _currentLocation)
{
	_newLocation.posX = _currentLocation.posX;
	_newLocation.posY = _currentLocation.posY;

	return _newLocation;
}
