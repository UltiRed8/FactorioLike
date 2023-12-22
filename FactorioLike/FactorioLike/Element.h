#pragma once

#include "Location.h"

class Element {

protected:
	Location location;
	char sign;

public:
	char GetSign() const {
		return sign;
	}

public:
	void SetLocation(const Location& _newLocation) {
		location = _newLocation;
	}

public:
	Element(const char _sign);
};

ostream& operator << (ostream& _stream, Element* _element);