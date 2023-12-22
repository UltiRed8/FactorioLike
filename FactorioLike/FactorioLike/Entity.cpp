#include "Entity.h"

Entity::Entity(const float _maxHp,const char _sign) : Element(_sign)
{
	hp.currentValue = _maxHp;
	hp.maxValue = _maxHp;
}

void Entity::Move(const Location& _deltaLoc)
{
	Location _newLocation = location;
	_newLocation += _deltaLoc;
	bool _updateLoc = GameManager::GetInstance().GetMap()->MoveElement(location,_newLocation);

	if (_updateLoc)
	{
		location = _newLocation;
	}
}

void Entity::DisplayStatistics(const bool _top, const bool _bottom) const {
	if (_top) cout << "##################################" << endl;
	hp.Display("HP", L'\u2665', 5, 20);
	if (_bottom) cout << "##################################" << endl;
}
