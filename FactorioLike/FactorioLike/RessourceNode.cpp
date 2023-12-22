#include "RessourceNode.h"

RessourceNode::RessourceNode(const NodeRarity& _rarity, const string& _type) : Element('R') {
	rarity = _rarity;
	type = _type;
	isAvailable = true;
}