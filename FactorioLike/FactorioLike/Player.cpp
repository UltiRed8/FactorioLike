#include "Player.h"

Player::Player() : Entity(hp.maxValue, GREEN "P" COLORRESET)
{
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
		if (!IsInInventory()) Direction({ -1, 0 });
		else inventory.MoveCursor({ 0, -1 });
		});
	_manager->AddKeybind({ 'q', 75 }, [&]() {
		if (!IsInInventory()) Direction({ 0, -1 });
		else inventory.MoveCursor({ -1, 0 });
		});
	_manager->AddKeybind({ 's', 80 }, [&]() {
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
		else EscapeMenu();
		});
}

Player::Player(const float _maxHunger, const float _maxThirst, const float _maxHp) : Entity(_maxHp, GREEN "P" COLORRESET)
{
	state = PS_GAME;
	hunger = { _maxHunger,_maxHunger };
	thirst = { _maxThirst,_maxThirst };
	inventory = Inventory();
	InitKeybinds();
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

void Player::BuildMenu() {
	if (state != PS_GAME) return;
	state = PS_BUILDING;
	system("CLS");
	// TODO a coder
}

void Player::EscapeMenu() {
	if (state != PS_GAME) return;
	state = PS_ESCAPE;
	system("CLS");
	// TODO a coder
	// bouton revenir en jeu (+ réappuyer sur echap ==> passer la méthode en toggle comme le toggleinventory)
	// bouton sauvegarder (pas de sauvegarde automatique)
	// bouton charger (charge la même save file)
	// bouton quitter
}

void Player::ToggleInventory()
{
	if (state == PS_GAME) {
		state = PS_INVENTORY;
		inventory.DisplayInventory();
	} else if (state == PS_INVENTORY) {
		system("CLS");
		state = PS_GAME;
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
		if (_ressourceNode = dynamic_cast<RessourceNode*>(_element))
		{
			const int _miningByHandsQuantity = 1;
			const string _ressourceName = _ressourceNode->GetType().GetName();
			string _message = "Interaction effectuée: Ressource Node " + _ressourceNode->GetStringNodeRarity() + " (" + _ressourceName + ")";
			if (_ressourceNode->GetToolsIDToCollect() == "" || inventory.ContainItem(_ressourceNode->GetToolsIDToCollect(), _miningByHandsQuantity))
			{
				inventory.AddItem(new Item(_ressourceNode->GetType()), _miningByHandsQuantity);
				_message += "\n+ " + to_string(_miningByHandsQuantity) + " " + _ressourceName + "\n";
			}
			else _message += "\nVous n'avez pas l'outil nécessaire pour récupérer la ressource !\n";
			GameManager::GetInstance()->SetGameMessage(_message, 1);
		}
	}
}