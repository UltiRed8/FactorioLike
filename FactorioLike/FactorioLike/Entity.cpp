#include "Entity.h"

Entity::Entity() : Element() {}

Entity::Entity(const float _maxHp) : Element() {
	hp.currentValue = _maxHp;
	hp.maxValue = _maxHp;
}

void Entity::Move(const Location& _deltaLoc) {
	cout << "Moved to " << _deltaLoc.posX << " " << _deltaLoc.posY << endl; // TODO debug, a enlever quand on aura les déplacements
	/*bool _updateLoc = GameManager::GetInstance().GetMap()->MoveElement(location,location + _deltaLoc);
	if (_updateLoc) location += _deltaLoc;*/
}

void Entity::DisplayStatistics(const bool _top, const bool _bottom) const {
	if (_top) cout << "##################################" << endl;
	hp.Display("HP", L'\u2665', 5, 20);
	if (_bottom) cout << "##################################" << endl;
}
