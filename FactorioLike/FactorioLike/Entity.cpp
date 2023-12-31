#include "Entity.h"

Entity::Entity(const float _maxHp, const string _sign) : Element(_sign)
{
	hp.currentValue = _maxHp;
	hp.maxValue = _maxHp;
}

bool Entity::Move(const Location& _deltaLoc)
{
	Location _newLocation = location;
	_newLocation += _deltaLoc;
	if (GameManager::GetInstance()->GetMap()->MoveElement(location, _newLocation))
	{
		location += _deltaLoc;
		return true;
	}
	return false;
}

void Entity::DisplayStatistics(const bool _top, const bool _bottom) const
{
	if (_top) cout << "##################################" << endl;
	hp.Display("HP", RED, L'\u2665', 5, 20);
	if (_bottom) cout << "##################################" << endl;
}
