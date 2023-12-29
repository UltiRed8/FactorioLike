#include "RessourceNode.h"

RessourceNode::RessourceNode(const NodeRarity& _rarity, const string& _type) : Element("R")
{
	rarity = _rarity;
	type = _type;
	isAvailable = true;
	UpdateSign();
}

void RessourceNode::UpdateSign()
{
	map<string, string> _signs
	{
		{ "wood", BROWN "R" WHITE },
		{ "stone", GRAY "R" WHITE },
		{ "coal", DARK_GRAY "R" WHITE },
		{ "iron_ore", YELLOW "R" WHITE },
	};
	sign = _signs[type];
}