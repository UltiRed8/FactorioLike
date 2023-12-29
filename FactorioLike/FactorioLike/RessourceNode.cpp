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
		make_pair("wood", BROWN "R" WHITE),
		make_pair("stone", GRAY "R" WHITE),
		make_pair("coal", DARK_GRAY "R" WHITE),
		make_pair("iron_ore", YELLOW "R" WHITE),
	};
	sign = _signs[type];
}