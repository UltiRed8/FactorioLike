#include "Entity.h"

Entity::Entity() : Element() {}

Entity::Entity(const float _maxHp) : Element()
{
	hp.currentValue = _maxHp;
	hp.maxValue = _maxHp;
}

void Entity::Move(const Location& _deltaLoc)
{
	//bool _updateLoc = GameManager::GetInstance().GetMap()->MoveElement(location,location + _deltaLoc);

	/*if (_updateLoc)
	{
		location += _deltaLoc;
	}*/
}
