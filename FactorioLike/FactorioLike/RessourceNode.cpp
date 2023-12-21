#include "RessourceNode.h"

RessourceNode::RessourceNode(const NodeRarity& _rarity, const RessourceType& _type)
{
	rarity = _rarity;
	type = _type;
	isAvailable = true;
}
