#pragma once

#include "Element.h"

#include <vector>
#include <iostream>

using namespace std;

class Map
{
	int viewDistance;
	int size;
	vector<vector<Element*>> grid;

public:
	Map(const int _size);

private:
	bool IsInRange(const Location& _location) const;
	void Generate();
	void Init();
	bool IsEmptySpace(const Location& _location) const;
	vector<vector<Element*>> GetViewport(const Location& _center);

public:
	void Display();
	bool MoveElement(const Location& _defaultLocation, const Location& _newLocation);
};

