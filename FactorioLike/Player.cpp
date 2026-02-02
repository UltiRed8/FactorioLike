#include "Player.h"

Player::Player() : Entity(100, GREEN "P" COLORRESET)
{
	currentMenu = nullptr;
	state = PS_GAME;
	hunger = { 100,100 };
	thirst = { 100,100 };
	inventory = Inventory();
	InitKeybinds();
	wantsToBuild = 0;
	InitMachinesCosts();
}

Player::Player(const float _maxHunger, const float _maxThirst, const float _maxHp) : Entity(_maxHp, GREEN "P" COLORRESET)
{
	wantsToBuild = 0;
	currentMenu = nullptr;
	state = PS_GAME;
	hunger = { _maxHunger,_maxHunger };
	thirst = { _maxThirst,_maxThirst };
	inventory = Inventory();
	InitKeybinds();
	InitMachinesCosts();
}

Player::~Player()
{
	DeleteMenu();
}

void Player::InitKeybinds()
{
	InputManager* _manager = InputManager::GetInstance();
	_manager->AddKeybind({ 'w', 72 }, [&]() {
		if (currentMenu)
		{
			currentMenu->ChangeSelected(-1);
			return;
		}
		if (!IsInInventory()) Direction({ -1, 0 });
		else inventory.MoveCursor({ 0, -1 });
		});
	_manager->AddKeybind({ 'a', 75 }, [&]() {
		if (!IsInInventory()) Direction({ 0, -1 });
		else inventory.MoveCursor({ -1, 0 });
		});
	_manager->AddKeybind({ 's', 80 }, [&]() {
		if (currentMenu)
		{
			currentMenu->ChangeSelected(1);
			return;
		}
		if (!IsInInventory()) Direction({ 1, 0 });
		else inventory.MoveCursor({ 0, 1 });
		});
	_manager->AddKeybind({ 'd', 77 }, [&]() {
		if (!IsInInventory()) Direction({ 0, 1 });
		else inventory.MoveCursor({ 1, 0 });
		});
	_manager->AddKeybind({ 'e' }, [&]() { ToggleInventory(); });
	_manager->AddKeybind({ 'b' }, [&]() { BuildMenu(); });
	_manager->AddKeybind({ 27 }, [&]() {
		if (IsInInventory()) ToggleInventory();
		else if (state == PS_BUILDING) CloseMenu();
		else EscapeMenu();
		});
	_manager->AddKeybind({ 32, '\n' }, [&]() { if (currentMenu)
	{
		currentMenu->ExecuteSelected();
		CloseMenu();
	}
		});
	wantsToBuild = MT_NONE;
}

void Player::UpdateVital(const VitalType& _type, const float _amount)
{
	switch (_type)
	{
		case VT_NONE:
			break;
		case VT_HP:
			UpdateVital(_amount, hp);
			break;
		case VT_HUNGER:
			UpdateVital(_amount, hunger);
			break;
		case VT_THRIST:
			UpdateVital(_amount, thirst);
			break;
		default:
			break;
	}
}

void Player::DisplayStatistics(const bool _top, const bool _bottom) const
{
	if (_top) cout << "##################################" << endl;
	hunger.Display("HUNGER", GREEN, '@', 1, 20);
	thirst.Display("THIRST", LIGHT_BLUE, '@', 1, 20);
	Entity::DisplayStatistics(false, _bottom);
}

bool Player::UseRessourceForBuildable(map<string, int>& _buildableCost)
{
	bool _hasEverything = true;
	for (map<string, int>::iterator _iterator = _buildableCost.begin(); _iterator != _buildableCost.end(); _iterator++)
	{
		if (!inventory.ContainItem(_iterator->first, _iterator->second))
		{
			_hasEverything = false;
			break;
		}
	}
	if (_hasEverything)
	{
		for (map<string, int>::iterator _iterator = _buildableCost.begin(); _iterator != _buildableCost.end(); _iterator++)
		{
			inventory.RemoveItem(new Item(_iterator->first), _iterator->second);
		}
		return true;
	}
	return false;
}

void Player::BuildMenu()
{
	if (state == PS_GAME)
	{
		state = PS_BUILDING;
		DeleteMenu();
		vector<Button> _buttons;
		_buttons.push_back(Button("CraftingTable (Wood*20)", [&]() { wantsToBuild = 1; }));
		_buttons.push_back(Button("Constructor (Wood*50 + Stick*20 + Wooden Pickaxe*5 + Wooden Sword*2)", [&]() { wantsToBuild = 2; }));
		_buttons.push_back(Button("Smelter (Stone*20 + Wood*15)", [&]() { wantsToBuild = 3; }));
		_buttons.push_back(Button("Collector (Wood*10 + Wooden Pickaxe*8)", [&]() { wantsToBuild = 4; }));
		currentMenu = new Menu("BUILD MENU", _buttons);
	}
	else if (state == PS_BUILDING)
	{
		CloseMenu();
	}
}

void Player::DeleteMenu()
{
	if (currentMenu) {
		delete currentMenu;
		currentMenu = nullptr;
	}
}

void Player::CloseMenu()
{
	DeleteMenu();
	state = PS_GAME;
}

string Player::GetSaveLine() const
{
	return "Player:" + to_string(location.posX) + ":" + to_string(location.posY) + ":" + to_string(hp.currentValue) + ":" + to_string(thirst.currentValue) + ":" + to_string(hunger.currentValue);
}

void Player::Load(const vector<string>& _list)
{
	hp.currentValue = stof(_list[3]);
	thirst.currentValue = stof(_list[4]);
	hunger.currentValue = stof(_list[5]);
}

void Player::EscapeMenu()
{
	if (state == PS_GAME)
	{
		state = PS_ESCAPE;
		DeleteMenu();
		vector<Button> _buttons =
		{
			Button("Resume", nullptr),
			Button("Save", [&]() { GameManager::GetInstance()->SaveGame(); }),
			Button("Load", [&]() { GameManager::GetInstance()->LoadGame(); }),
			Button("Quit", [&]() { GameManager::GetInstance()->SetWantsToQuit(true); }),
		};
		currentMenu = new Menu("PAUSE", _buttons);
	}
	else if (state == PS_ESCAPE)
	{
		CloseMenu();
	}
}

void Player::ToggleInventory()
{
	if (state == PS_GAME)
	{
		state = PS_INVENTORY;
		inventory.DisplayInventory();
	}
	else if (state == PS_INVENTORY)
	{
		CloseMenu();
	}
}
void Player::InitMachinesCosts()
{
	machinesCosts =
	{
		{ make_pair("wood", 20) },
		{ make_pair("wood", 50), make_pair("stick", 20), make_pair("wooden_pickaxe", 5), make_pair("wooden_sword", 2) },
		{ make_pair("stone", 20), make_pair("wood", 15) },
		{ make_pair("wood", 10), make_pair("wooden_pickaxe", 8) },
	};
}


void Player::UpdateVital(const float _amount,ProgessBar& _value)
{
	float currentValue = _value.currentValue;
	float maxValue = _value.maxValue;
	currentValue = currentValue + _amount >= maxValue ? maxValue : currentValue + _amount;
	_value.currentValue = currentValue;
}

void Player::Direction(const Location& _direction)
{
	if (wantsToBuild != MT_NONE)
	{
		PlaceBuildable(_direction);
		return;
	}
	if (!Move(_direction))
	{
		Location _target = location;
		_target += _direction;
		Element* _element = GameManager::GetInstance()->GetMap()->GetElementAt(_target);
		RessourceNode* _ressourceNode;
		Machine* _machine;
		if (_ressourceNode = dynamic_cast<RessourceNode*>(_element))
		{
			const int _miningByHandsQuantity = 1;
			const string _ressourceName = _ressourceNode->GetType().GetName();
			string _message = "Interaction done: Resource Node " + _ressourceNode->GetStringNodeRarity() + " (" + _ressourceName + ")";
			string _toolsToGet = _ressourceNode->GetToolsIDToCollect();
			vector<string> _listOfToolsID = SplitString(_toolsToGet, ' ');
			if (_toolsToGet.empty())
			{
				inventory.AddItem(new Item(_ressourceNode->GetType()), _miningByHandsQuantity);
				_message += "\n+ " + to_string(_miningByHandsQuantity) + " " + _ressourceName + "\n";
				GameManager::GetInstance()->SetGameMessage(_message, 1);
				return;
			}
			for (const string& _toolID : _listOfToolsID)
			{
				if (inventory.ContainItem(_toolID, 1))
				{
					inventory.AddItem(new Item(_ressourceNode->GetType()), _miningByHandsQuantity);
					_message += "\n+ " + to_string(_miningByHandsQuantity) + " " + _ressourceName + "\n";
					GameManager::GetInstance()->SetGameMessage(_message, 1);
					return;
				}
			}
			_message += "\nYou do not have the necessary tools to get that resource!\n";
			GameManager::GetInstance()->SetGameMessage(_message, 1);
		}
		else if (_machine = dynamic_cast<Machine*>(_element))
		{
			if (!_machine->HasRecipes()) return;
			state = PS_BUILDING;
			_machine->SwitchRecipe(this);
		}
	}
}

void Player::PlaceBuildable(const Location& _direction)
{
	Location _target = location;
	_target += _direction;
	GameManager* _gm = GameManager::GetInstance();
	vector<vector<Element*>>& _grid = _gm->GetMap()->GetGrid();
	Element* _elementAtTarget = _grid[_target.posX][_target.posY];
	if (wantsToBuild == MT_COLLECTOR)
	{
		if (!_elementAtTarget || !dynamic_cast<RessourceNode*>(_elementAtTarget))
		{
			_gm->SetGameMessage("You need to place a collector on a resource!", 1);
		}
		else
		{
			if (!UseRessourceForBuildable(machinesCosts[static_cast<const int>(wantsToBuild) - 1]))
			{
				_gm->SetGameMessage("You do not have the resources needed!", 1);
			}
			else
			{
				RessourceNode* _node = dynamic_cast<RessourceNode*>(_elementAtTarget);
				Machine* _machine = new Machine(static_cast<MachineType>(wantsToBuild));
				_machine->SetLocation(_target);
				_machine->SetNode(_node);
				_grid[_target.posX][_target.posY] = _machine;
			}
		}
	}
	if (_elementAtTarget)
	{
		_gm->SetGameMessage("You need to place the machine on an empty tile!", 1);
	}
	else
	{
		if (!UseRessourceForBuildable(machinesCosts[static_cast<const int>(wantsToBuild) - 1]))
		{
			_gm->SetGameMessage("You do not have the resources needed!", 1);
		}
		else
		{
			Machine* _machine = new Machine(static_cast<MachineType>(wantsToBuild));
			_machine->SetLocation(_target);
			_grid[_target.posX][_target.posY] = _machine;
		}
	}
	wantsToBuild = MT_NONE;
}