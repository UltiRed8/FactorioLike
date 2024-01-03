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
			cout << "Interaction effectuée: Ressource Node " << _ressourceNode->GetStringNodeRarity() << " (" << _ressourceNode->GetType() << ")" << endl;
			int _miningByHandsQuantity = 1;
			if (_ressourceNode->GetToolsIDToCollect() == "" || inventory.ContainItem(_ressourceNode->GetToolsIDToCollect(), _miningByHandsQuantity)) {
				inventory.AddItem(new Item("NAME", _ressourceNode->GetType()), _miningByHandsQuantity);
				cout << "+ " << _miningByHandsQuantity << " " << _ressourceNode->GetType() << endl;
			} else cout << "Vous n'avez pas l'outil nécessaire pour récupérer la ressource !" << endl;

			system("PAUSE");
		}
	}
}