#pragma once
#include "ItemType.h"
#include "Element.h"
#include <string>

using namespace std;

enum NodeRarity
{
	NR_NONE, NR_COMMUN = 30, NR_RARE = 45, NR_EPIC = 70 , NR_LEGENDARY = 100
};

class RessourceNode : public Element
{
	NodeRarity rarity;
	string type;
	bool isAvailable;

public:
	bool GetIsAvailable() const
	{
		return isAvailable;
	}

	NodeRarity GetRarity() const
	{
		return rarity;
	}

public:
	RessourceNode(const NodeRarity& _rarity, const string& _type);

};

