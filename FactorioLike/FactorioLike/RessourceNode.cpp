#include "RessourceNode.h"

RessourceNode::RessourceNode(const NodeRarity& _rarity, const string& _type) : Element("R")
{
	rarity = _rarity;
	type = Ressource(_type);
	toolIDToCollect = "";
	UpdateSign();
}

RessourceNode::RessourceNode(const vector<string>& _list) : Element("R")
{
	Load(_list);
	toolIDToCollect = "";
	UpdateSign();
}

void RessourceNode::Load(const vector<string>& _list)
{
	location.posX = stoi(_list[1]);
	location.posY = stoi(_list[2]);
	rarity = static_cast<NodeRarity>(stoi(_list[3]));
	type = Ressource(_list[4]);
}

string RessourceNode::GetSaveLine() const
{
	return "RessourceNode:" + to_string(location.posX) + ":" + to_string(location.posY) + ":" + to_string(rarity) + ":" + type.GetID();
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
	sign = _signs[type.GetID()];
	map<string, string> _toolsToCollect
	{
		{ "wood", "" },
		{ "stone", "wooden_pickaxe stone_pickaxe" },
		{ "coal", "stone_pickaxe" },
		{ "iron_ore", "stone_pickaxe" },
	};
	toolIDToCollect = _toolsToCollect[type.GetID()];
}