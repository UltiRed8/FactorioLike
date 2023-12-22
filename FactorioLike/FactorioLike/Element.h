#pragma once

#include "Location.h"

class Element {

protected:
	Location location;

public:
	void SetLocation(const Location& _newLocation) {
		location = _newLocation;
	}

public:
	Element();
};