#pragma once

#include "Location.h"
#include "Saveable.h"

class Element : public Saveable
{

protected:
	Location location;
	string sign;

public:
	string GetSign() const
	{
		return sign;
	}

public:
	Location GetLocation() const
	{
		return location;
	}
	void SetLocation(const Location& _newLocation)
	{
		location = _newLocation;
	}

public:
	Element(const string _sign);
	virtual ~Element() {};
};

ostream& operator << (ostream& _stream, Element* _element);