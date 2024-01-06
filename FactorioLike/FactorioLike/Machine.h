#pragma once

#include "Buildable.h"
#include "Item.h"

enum MachineType
{
	MT_NONE, MT_MANUALCRAFTER, MT_CRAFTER, MT_SMELTER, MT_COLLECTOR
};

struct Recipe
{
	int id;
	MachineType recipeFor;
	map<string, int> inputs;
	float processingDelay;
	map<string, int> outputs;

public:
	Recipe()
	{
		id = -1;
		recipeFor = MT_NONE;
		inputs = map<string, int>();
		processingDelay = 0.0f;
		outputs = map<string, int>();
	}
	Recipe(const int _recipeID, MachineType _recipeFor, map<string, int> _inputs, float _processingDelay, map<string, int> _outputs)
	{
		id = _recipeID;
		recipeFor = _recipeFor;
		inputs = _inputs;
		processingDelay = _processingDelay;
		outputs = _outputs;
	}
};

bool operator == (const Recipe& _recipe1, const	Recipe& _recipe2);

class Machine : public Buildable
{
	MachineType type;
	Recipe selectedRecipe;
	vector<Recipe> availableRecipes;
	int delay;
	int currentDelay;
	RessourceNode* node;

public:
	vector<Recipe> GetAvailableRecipes() const
	{
		return availableRecipes;
	}
	bool HasRecipes() const {
		return static_cast<const int>(availableRecipes.size()) >= 1;
	}

public:
	Machine();
	Machine(const vector<string>& _list);
	Machine(const MachineType _type);
	~Machine();

private:
	void InitRecipes();
	void ComputeDelay();
	void Execute();
	void UpdateSign();

public:
	void SelectRecipe(const Recipe _recipe);
	void Tick();
	virtual void Load(const vector<string>& _list) override;
	virtual string GetSaveLine() const override;
};