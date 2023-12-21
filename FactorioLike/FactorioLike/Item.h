#pragma once
#include "ItemType.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Item
{
protected:
	string name;

public:
	string GetName() const
	{
		return name;
	}

public:
	Item();
	Item(const string& _name);

public:
	vector<string> GetDisplay(const int _targetLength,const string& _count) const;
	
};

struct Ressource : public Item
{
	string type;

public:
	Ressource() : Item()
	{
		type = RT_NONE;
	}

	Ressource(const string& _type,const string& _name) : Item(_name)
	{
		type = _type;
	}
};


struct Consumable : public Item
{
	ConsumableType type;

public:
	Consumable() : Item()
	{
		type = CT_NONE;
	}

	Consumable(ConsumableType _type, const string& _name) : Item(_name)
	{
		type = _type;
	}

};
