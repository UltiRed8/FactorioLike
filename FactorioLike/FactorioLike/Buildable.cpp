#include "Buildable.h"

Buildable::Buildable(const char _sign) : Element(_sign) {
	buildableLife = { -1.0f, -1.0f };
}

Buildable::Buildable(const float _buildableLife, const char _sign) : Element(_sign) {
	buildableLife = { _buildableLife, _buildableLife };
}

void Buildable::ApplyDamages(const float _amount) {
	buildableLife.currentValue -= _amount;
	if (buildableLife.currentValue <= 0.0f) Destroy();
}

void Buildable::Destroy() {
	GameManager::GetInstance().GetMap()->RemoveElement(location);
}
