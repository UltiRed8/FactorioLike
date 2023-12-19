#pragma once

#include "Element.h"

#include <vector>
#include <iostream>

using namespace std;

// TODO a enlever après le merge main
struct Location
{
	int _posX = 0;
	int _posY = 0;
};
// TODO a enlever après le merge main

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
	vector<vector<Element*>> GetViewport(const Location& _center);

public:
	void Display();
};

