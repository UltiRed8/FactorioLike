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
	string id;

public:
	string GetID() const
	{
		return id;
	}
	string GetName() const
	{
		return name;
	}

public:
	Item();
	Item(const string& _name, const string& _id);

public:
	vector<string> GetDisplay(const int _targetLength,const string& _count) const;
	
};

struct Ressource : public Item
{
	RessourceType type;

public:
	Ressource() : Item()
	{
		type = RT_NONE;
	}

	Ressource(RessourceType _type,const string& _name, const string& _id) : Item(_name, _id)
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

	Consumable(ConsumableType _type, const string& _name, const string& _id) : Item(_name, _id)
	{
		type = _type;
	}

};
