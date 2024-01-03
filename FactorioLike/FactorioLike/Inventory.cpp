#include "Inventory.h"

Inventory::Inventory() {
	itemsPerLine = 5;
	slotsUsed = 0;
	maxItem = 24;
	inventory = vector<Slot*>();
}

Inventory::~Inventory() {
	for (const Slot* _item : inventory) delete _item;
}

bool Inventory::AddItem(Item* _item, const int _amount) {
	for (Slot* _slot : inventory) {
		if (_slot->item->GetName() == _item->GetName()) {
			_slot->itemAmount += _amount;
			delete _item;
			return true;
		}
	}
	const int _size = static_cast<const int>(inventory.size());
	if (_size >= maxItem) return false;
	inventory.push_back(new Slot(_item, _amount));
	slotsUsed++;
	return true;
}

bool Inventory::ContainItem(const string& _itemID, const int _amount) {
	for (Slot* _slot : inventory) {
		if (_slot->item->GetID() == _itemID) {
			if (_slot->itemAmount >= _amount) return true;
		}
	}
	return false;
}

int Inventory::GetLongestName() {
	int _longest = 0;
	for (Slot* _slot : inventory) {
		int _lenght = static_cast<int>(_slot->item->GetName().length());
		if (_lenght > _longest) _longest = _lenght;
	}
	return _longest;
}

bool Inventory::RemoveItem(Item* _item, const int _amount) {
	if (inventory.empty() || !ContainItem(_item->GetID(), _amount)) {
		delete _item;
		return false;
	}
	int _index = 0;
	for (Slot* _slot : inventory) {
		if (_slot->item->GetName() == _item->GetName()) {
			_slot->itemAmount -= _amount;
			if (_slot->itemAmount <= 0) {
				inventory.erase(inventory.begin() + _index);
				delete _slot;
				slotsUsed--;
			}
			delete _item;
			return true;
		}
		_index++;
	}
	delete _item;
	return false;
}

void Inventory::MoveCursor(const Location& _deltaLoc) {
	cursorLocation += _deltaLoc;
	const int _minimalAmountInColumn = static_cast<int>(floor(slotsUsed / itemsPerLine - 1));
	const int _amountInCurrentColumn = (cursorLocation.posX <= slotsUsed % itemsPerLine-1) ? _minimalAmountInColumn +1 : _minimalAmountInColumn;
	if (cursorLocation.posY > _amountInCurrentColumn) cursorLocation.posY = 0;
	else if (cursorLocation.posY < 0) cursorLocation.posY = _amountInCurrentColumn;
	if (cursorLocation.posX > itemsPerLine-1) cursorLocation.posX = 0;
	else if (cursorLocation.posX < 0) cursorLocation.posX = itemsPerLine-1;
	DisplayInventory();
}

void Inventory::DisplayInventory() {
	system("CLS");
	vector<vector<string>> _elements;
	const int _lines = 5;
	const int _longestName = GetLongestName();
	for (Slot* _slot : inventory) {
		_elements.push_back(_slot->item->GetInventoryDisplay(_longestName,_slot->GetDisplayAmount()));
	}
	const int _size = static_cast<int>(_elements.size());
	int _offset = 0;
	cout << GREEN;
	const int _dividerSize = (((_longestName + 4)+1) * itemsPerLine)-1;
	for (int _i = 0; _i < _dividerSize / 2 - 6; _i++) cout << "=";
	cout << " INVENTAIRE ";
	for (int _i = 0; _i < _dividerSize / 2 - 5; _i++) cout << "=";
	cout << COLORRESET << endl << endl;
	do {
		for (int _index = 0; _index < _lines; _index++) {
			for (int _index2 = _offset; _index2 < _offset + itemsPerLine; _index2++) {
				if (_index2 >= _size) continue;
				if (_index2 == cursorLocation.posX + (cursorLocation.posY * itemsPerLine)) cout << LIME;
				else cout << COLORRESET;
				cout << _elements[_index2][_index];
			}
			cout << endl;
		}
		_offset += itemsPerLine;
	} while (_offset <= _size);
	cout << GREEN;
	for (int _i = 0; _i < _dividerSize; _i++) cout << "=";
	cout << COLORRESET << endl << endl;
}
