#pragma once

#include "Element.h"
#include "FileManager.h"
#include "RessourceNode.h"
#include "Colors.h"

#include <vector>
#include <iostream>

class Player;

using namespace std;

struct GenerationSetting
{
	string type;
	int nodeAmount;

public:
	GenerationSetting(const string& _line)
	{
		int _index = static_cast<int>(_line.find_first_of(":"));
		type = _line.substr(0, _index);
		nodeAmount = stoi(_line.substr(_index + 1, static_cast<int>(_line.size())));
	}
};

class Map
{
	int viewDistance;
	int size;
	vector<vector<Element*>> grid;
	Player* player;

public:
	vector<vector<Element*>> GetGrid() const
	{
		return grid;
	}
	Player* GetPlayer() const
	{
		return player;
	}

public:
	Map(const int _size, Player* _player);

private:
	bool IsInRange(const Location& _location) const;
	void Generate();
	void Init();
	bool IsEmptySpace(const Location& _location) const;
	vector<vector<Element*>> GetViewport(const Location& _center);

public:
	void Display();
	bool MoveElement(const Location& _defaultLocation, const Location& _newLocation);
	void RemoveElement(const Location& _location);
	Element* GetElementAt(const Location& _target);
};