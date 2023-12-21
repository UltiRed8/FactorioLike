#pragma once

#include "Element.h"
#include "Item.h"
#include <vector>
#include <iostream>

using namespace std;

struct GenerationSetting
{
	Ressource ressource;
	int nodeAmount;

public:
	GenerationSetting(const string& _type, const string& _name, const int _amount)
	{
		ressource = Ressource(_type, _name);
		nodeAmount = _amount;
	}
};

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

