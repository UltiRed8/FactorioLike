#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "FileManager.h"

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
	Item(const string& _id);

private:
	void GetNameFromConfig();

public:
	vector<string> GetInventoryDisplay(const int _targetLength,const string& _count) const;
};

struct Ressource : public Item
{

public:
	Ressource() : Item()
	{

	}

	Ressource(const string& _id) : Item(_id)
	{

	}
};