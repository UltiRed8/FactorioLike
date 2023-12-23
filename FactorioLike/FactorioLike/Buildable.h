#pragma once

#include "Element.h"
#include "ProgressBar.h"
#include "GameManager.h"

class Buildable : public Element {
protected:
	ProgessBar buildableLife;

public:
	bool IsUndestructable() const {
		return buildableLife.maxValue == -1.0f;
	}

public:
	Buildable(const char _sign);
	Buildable(const float _maxLife, const char _sign);

public:
	void ApplyDamages(const float _amount);
	void Destroy();
};