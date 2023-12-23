#pragma once

#include "Buildable.h"
#include "Item.h"

enum MachineType {
	MT_NONE, MT_CRAFTER, MT_SMELTER
};

struct Recipe {
	MachineType recipeFor;
	map<string, int> inputs;
	float processingDelay;
	map<string, int> outputs;

public:
	Recipe() {
		recipeFor = MT_NONE;
		inputs = map<string, int>();
		processingDelay = 0.0f;
		outputs = map<string, int>();
	}
	Recipe(MachineType _recipeFor, map<string, int> _inputs, float _processingDelay, map<string, int> _outputs) {
		recipeFor = _recipeFor;
		inputs = _inputs;
		processingDelay = _processingDelay;
		outputs = _outputs;
	}
};

bool operator == (const Recipe& _recipe1, const	Recipe& _recipe2);

class Machine : public Buildable {
	MachineType type;
	Recipe selectedRecipe;
	vector<Recipe> availableRecipes;
	int delay;
	int currentDelay;

public:
	vector<Recipe> GetAvailableRecipes() const {
		return availableRecipes;
	}

public:
	Machine(const MachineType _type);

private:
	void InitRecipes();
	void ComputeDelay();
	void Execute();

public:
	void SelectRecipe(const Recipe _recipe);
	void Tick();
};