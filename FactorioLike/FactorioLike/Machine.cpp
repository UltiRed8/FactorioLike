#include "Machine.h"

Machine::Machine(const MachineType _type) : Buildable(-1.0f, "?") {
	type = _type;
	if (type == MT_CRAFTER) sign = 'C';
	else if (type == MT_SMELTER) sign = 'S';
	delay = currentDelay = -1;
}

void Machine::InitRecipes() {
	if (type == MT_CRAFTER) {
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("wood", 2) }, 1.0f, { make_pair("stick", 1) }));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("wood", 3), make_pair("stick", 2) }, 1.0f, { make_pair("wooden_pickaxe", 1) }));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("wood", 2), make_pair("stick", 1) }, 1.0f, { make_pair("wooden_sword", 1) }));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("stone", 3), make_pair("stick", 2) }, 1.0f, { make_pair("stone_pickaxe", 1) }));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("stone", 2), make_pair("stick", 1) }, 1.0f, { make_pair("stone_sword", 1) }));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("iron_ingot", 2) }, 1.0f, { make_pair("iron_rod", 1) }));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("iron_ingot", 3), make_pair("iron_rod", 2)}, 1.0f, {make_pair("iron_pickaxe", 1)}));
		availableRecipes.push_back(Recipe(MT_CRAFTER, { make_pair("iron_ingot", 100), make_pair("iron_rod", 20)}, 1.0f, {make_pair("heavy_iron_sword", 1)}));
	} else if (type == MT_SMELTER) {
		availableRecipes.push_back(Recipe(MT_SMELTER, { make_pair("iron_ore", 4), make_pair("coal", 1)}, 3.5f, {make_pair("iron_ingot", 2)}));
		availableRecipes.push_back(Recipe(MT_SMELTER, { make_pair("wood", 6), make_pair("coal", 1)}, 3.5f, {make_pair("coal", 4)}));
	}
}

void Machine::Execute() {
	// TODO enlever l'input de l'inventaire de la map
	// TODO donner l'output à l'inventaire de la map
}

void Machine::SelectRecipe(const Recipe _recipeToSet) {
	if (type == MT_NONE) return;
	for (const Recipe& _recipe : availableRecipes) {
		if (_recipe == _recipeToSet) {
			selectedRecipe = _recipe;
			return;
		}
	}
	ComputeDelay();
}

void Machine::ComputeDelay() {
	const int _ticksPerSeconds = GameManager::GetInstance()->GetTicksPerSeconds();
	delay = static_cast<int>(selectedRecipe.processingDelay* _ticksPerSeconds);
	currentDelay = delay;
}

void Machine::Tick() { // TODO ne pas oublier d'appeler les méthodes tick des machines dans le tick du game manager (dynamic cast des elements pour check if machine ?)
	if (type == MT_NONE) return;
	if (delay < 0) return;
	currentDelay--;
	if (currentDelay == 0) {
		currentDelay = delay;
		Execute();
	}
}

bool operator == (const Recipe& _recipe1, const	Recipe& _recipe2) {
	return ((_recipe1.inputs == _recipe2.inputs) &&
			(_recipe1.outputs == _recipe2.outputs)) &&
			((_recipe1.processingDelay == _recipe2.processingDelay) &&
			(_recipe1.recipeFor == _recipe2.recipeFor));
}