#include "Player.h"

Player::Player() : Entity(100, GREEN "P" COLORRESET)
{
	currentMenu = nullptr;
	state = PS_GAME;
	hunger = { 100,100 };
	thirst = { 100,100 };
	inventory = Inventory();
	InitKeybinds();
}

void Player::InitKeybinds()
{
	InputManager* _manager = InputManager::GetInstance();
	_manager->AddKeybind({ 'z', 72 }, [&]() {
		if (currentMenu)
		{
			currentMenu->ChangeSelected(-1);
			return;
		}
		if (!IsInInventory()) Direction({ -1, 0 });
		else inventory.MoveCursor({ 0, -1 });
	});
	_manager->AddKeybind({ 'q', 75 }, [&]() {
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
}

Player::Player(const float _maxHunger, const float _maxThirst, const float _maxHp) : Entity(_maxHp, GREEN "P" COLORRESET)
{
	currentMenu = nullptr;
	state = PS_GAME;
	hunger = { _maxHunger,_maxHunger };
	thirst = { _maxThirst,_maxThirst };
	inventory = Inventory();
	InitKeybinds();
}

Player::~Player()
{
	DeleteMenu();
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

void Player::BuildMenu()
{
	if (state == PS_GAME)
	{
		state = PS_BUILDING;
		DeleteMenu();
		vector<Button> _buttons =
		{
			Button("Etabli", [&]() {  }), // TODO
			Button("Constructeur", [&]() {  }), // TODO
			Button("Fondrie", [&]() {  }), // TODO
			Button("Collecteur de ressources", [&]() {  }), // TODO
		};
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
			Button("Reprendre", nullptr),
			Button("Sauvegarder", [&]() { GameManager::GetInstance()->SaveGame(); }),
			Button("Charger", [&]() { GameManager::GetInstance()->LoadGame(); }),
			Button("Quitter", [&]() { GameManager::GetInstance()->SetWantsToQuit(true); }),
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

void Player::UpdateVital(const float _amount,ProgessBar& _value)
{
	float currentValue = _value.currentValue;
	float maxValue = _value.maxValue;
	currentValue = currentValue + _amount >= maxValue ? maxValue : currentValue + _amount;
	_value.currentValue = currentValue;
}

void Player::Direction(const Location& _direction)
{
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
			string _message = "Interaction effectuée: Ressource Node " + _ressourceNode->GetStringNodeRarity() + " (" + _ressourceName + ")";
			string _toolsToGet = _ressourceNode->GetToolsIDToCollect();
			vector<string> _listOfToolsID = SplitString(_toolsToGet, ' ');
			if (static_cast<const int>(_listOfToolsID.size()) == 0)
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
			_message += "\nVous n'avez pas l'outil nécessaire pour récupérer la ressource !\n";
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