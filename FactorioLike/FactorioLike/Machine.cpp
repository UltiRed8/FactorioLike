#include "Machine.h"
#include "Player.h"

Machine::Machine() : Buildable(-1.0f, "?")
{
	type = MT_NONE;
	delay = currentDelay = -1;
	node = nullptr;
}

Machine::Machine(const vector<string>& _list) : Buildable(-1.0f, "?")
{
	type = MT_NONE;
	delay = currentDelay = -1;
	node = nullptr;
	Load(_list);
	UpdateSign();
}

Machine::Machine(const MachineType _type) : Buildable(-1.0f, "?")
{
	type = _type;
	UpdateSign();
	delay = currentDelay = -1;
	node = nullptr;
}

Machine::~Machine()
{
	if (node)
	{
		delete node;
		node = nullptr;
	}
}

void Machine::UpdateSign()
{
	if (type == MT_MANUALCRAFTER) sign = 'M';
	else if (type == MT_CRAFTER) sign = 'C';
	else if (type == MT_SMELTER) sign = 'S';
	else if (type == MT_COLLECTOR) sign = 'O';
}

void Machine::InitRecipes() {
	if (type == MT_MANUALCRAFTER || type == MT_CRAFTER)
	{
		availableRecipes.push_back(Recipe(1, MT_CRAFTER, { make_pair("wood", 2) }, 1.0f, { make_pair("stick", 1) }));
		availableRecipes.push_back(Recipe(2, MT_CRAFTER, { make_pair("wood", 3), make_pair("stick", 2) }, 1.0f, { make_pair("wooden_pickaxe", 1) }));
		availableRecipes.push_back(Recipe(3, MT_CRAFTER, { make_pair("wood", 2), make_pair("stick", 1) }, 1.0f, { make_pair("wooden_sword", 1) }));
		availableRecipes.push_back(Recipe(4, MT_CRAFTER, { make_pair("stone", 3), make_pair("stick", 2) }, 1.0f, { make_pair("stone_pickaxe", 1) }));
		availableRecipes.push_back(Recipe(5, MT_CRAFTER, { make_pair("stone", 2), make_pair("stick", 1) }, 1.0f, { make_pair("stone_sword", 1) }));
	}
	if (type == MT_CRAFTER)
	{
		availableRecipes.push_back(Recipe(6, MT_CRAFTER, { make_pair("iron_ingot", 2) }, 1.0f, { make_pair("iron_rod", 1) }));
		availableRecipes.push_back(Recipe(7, MT_CRAFTER, { make_pair("iron_ingot", 3), make_pair("iron_rod", 2)}, 1.0f, {make_pair("iron_pickaxe", 1)}));
		availableRecipes.push_back(Recipe(8, MT_CRAFTER, { make_pair("iron_ingot", 100), make_pair("iron_rod", 20)}, 1.0f, {make_pair("heavy_iron_sword", 1)}));
	}
	else if (type == MT_SMELTER)
	{
		availableRecipes.push_back(Recipe(9, MT_SMELTER, { make_pair("iron_ore", 4), make_pair("coal", 1)}, 3.5f, {make_pair("iron_ingot", 2)}));
		availableRecipes.push_back(Recipe(10, MT_SMELTER, { make_pair("wood", 6), make_pair("coal", 1)}, 3.5f, {make_pair("coal", 4)}));
	}
}

void Machine::Execute()
{
	Inventory& _inventory = GameManager::GetInstance()->GetPlayer()->GetInventory();
	if (type == MT_COLLECTOR)
	{
		_inventory.AddItem(new Item(node->GetType()), 1);
	}
	else
	{
		bool _hasEverything = true;
		for (map<string,int>::iterator _iterator = selectedRecipe.inputs.begin(); _iterator != selectedRecipe.inputs.end(); _iterator++)
		{
			if (!_inventory.ContainItem(_iterator->first, _iterator->second))
			{
				_hasEverything = false;
				break;
			}
		}
		if (_hasEverything)
		{
			for (map<string, int>::iterator _iterator = selectedRecipe.inputs.begin(); _iterator != selectedRecipe.inputs.end(); _iterator++)
			{
				_inventory.RemoveItem(new Item(_iterator->first), _iterator->second);
			}
			for (map<string, int>::iterator _iterator = selectedRecipe.outputs.begin(); _iterator != selectedRecipe.outputs.end(); _iterator++)
			{
				_inventory.AddItem(new Item(_iterator->first), _iterator->second);
			}
		}
	}
}

void Machine::SelectRecipe(const Recipe _recipeToSet)
{
	if (type == MT_NONE) return;
	if (!HasRecipes()) return;
	if (type == MT_MANUALCRAFTER)
	{
		for (const Recipe& _recipe : availableRecipes)
		{
			if (_recipe == _recipeToSet)
			{
				selectedRecipe = _recipe;
				Execute();
				return;
			}
		}
		return;
	}
	for (const Recipe& _recipe : availableRecipes)
	{
		if (_recipe == _recipeToSet)
		{
			selectedRecipe = _recipe;
			return;
		}
	}
	ComputeDelay();
}

void Machine::SwitchRecipe(Player* _player)
{
	_player->DeleteMenu();
	vector<Button> _buttons;
	for (Recipe& _recipe : availableRecipes)
	{
		string _textInput;
		for (map<string, int>::iterator _iterator = _recipe.inputs.begin(); _iterator != _recipe.inputs.end(); _iterator++)
		{
			if (!_textInput.empty()) _textInput += " + ";
			_textInput += Item(_iterator->first).GetName() + "*" + to_string(_iterator->second);
		}
		string _textOutput;
		for (map<string, int>::iterator _iterator = _recipe.outputs.begin(); _iterator != _recipe.outputs.end(); _iterator++)
		{
			if (!_textOutput.empty()) _textOutput += " + ";
			_textOutput += Item(_iterator->first).GetName() + "*" + to_string(_iterator->second);
		}
		_buttons.push_back(Button(_textInput + " -> " + _textOutput, [&]() {
			SelectRecipe(_recipe);
		}));
	}
	string _list[] = {"Unknown", "Etabli", "Constructeur", "Fondrie", "Collecteur"};
	_player->SetCurrentMenu(new Menu(_list[type], _buttons));
}

void Machine::ComputeDelay()
{
	const int _ticksPerSeconds = GameManager::GetInstance()->GetTicksPerSeconds();
	if (selectedRecipe.id == -1)
	{
		if (node)
		{
			delay = static_cast<int>(static_cast<int>((_ticksPerSeconds * 60) / node->GetRarity()));
			currentDelay = delay;
		}
	}
	else
	{
		delay = static_cast<int>(selectedRecipe.processingDelay * _ticksPerSeconds);
		currentDelay = delay;
	}
}

void Machine::Tick()
{
	if (type == MT_NONE) return;
	if (delay < 0) return;
	currentDelay--;
	if (currentDelay == 0)
	{
		Execute();
		currentDelay = delay;
	}
}

void Machine::Load(const vector<string>& _list)
{
	location.posX = stoi(_list[1]);
	location.posY = stoi(_list[2]);
	type = static_cast<MachineType>(stoi(_list[3]));
	InitRecipes();
	const int _selectedRecipe = stoi(_list[4]);
	if (static_cast<const int> (availableRecipes.size()) >= 1 && _selectedRecipe != -1) selectedRecipe = availableRecipes[_selectedRecipe];
	if (type == MT_COLLECTOR)
	{
		const vector<string> _nodeList = { _list.begin() + 5, _list.end() };
		node = new RessourceNode(_nodeList);
	}
	ComputeDelay();
}

string Machine::GetSaveLine() const
{
	int _index = 0;
	for (const Recipe& _recipe : availableRecipes)
	{
		if (_recipe == selectedRecipe) break;
		else _index++;
	}

	string _line = "Machine:" + to_string(location.posX) + ":" + to_string(location.posY) + ":" + to_string(type) + ":" + to_string(_index);
	if (node) return _line += ":" + node->GetSaveLine();
	return _line;
}

bool operator == (const Recipe& _recipe1, const	Recipe& _recipe2)
{
	return ((_recipe1.inputs == _recipe2.inputs) &&
			(_recipe1.outputs == _recipe2.outputs)) &&
			((_recipe1.processingDelay == _recipe2.processingDelay) &&
			(_recipe1.recipeFor == _recipe2.recipeFor));
}