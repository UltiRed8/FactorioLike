#pragma once

#include "Element.h"
#include "FileManager.h"
#include "RessourceNode.h"
#include "Macros.h"
#include "Item.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct GenerationSetting
{
	Ressource ressource;
	int nodeAmount;

public:
	GenerationSetting(const string& _line)
	{
		int _index = static_cast<int>(_line.find_first_of(":"));
		string _type = _line.substr(0, _index);
		nodeAmount = stoi(_line.substr(_index + 1,static_cast<int>(_line.size())));
		ressource = { _type , "" };
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

