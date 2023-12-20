#include "Inventory.h"

Inventory::Inventory()
{
	maxItem = 24;
	inventory = vector<Slot*>();
}

Inventory::~Inventory()
{
	for (const Slot* _item : inventory)
	{
		delete _item;
	}
}

bool Inventory::AddItem(Item* _item, const int _amount)
{
	for (Slot* _slot : inventory)
	{
		if (_slot->item->GetName() == _item->GetName())
		{
			_slot->itemAmount += _amount;
			delete _item;
			return true;
		}
	}
	const int _size = static_cast<const int>(inventory.size());
	if (_size >= maxItem) return false;
	inventory.push_back(new Slot(_item, _amount));
	return true;
	
}

bool Inventory::ContainItem(Item* _item, const int _amount)
{
	for (Slot* _slot : inventory)
	{
		if (_slot->item->GetName() == _item->GetName())
		{
			if (_slot->itemAmount >= _amount)
			{
				return true;
			}
		}
	}
	return false;
}

int Inventory::GetLongestName()
{
	int _longest = 0;
	for (Slot* _slot : inventory)
	{
		int _lenght = static_cast<int>(_slot->item->GetName().length());
		if (_lenght > _longest) _longest = _lenght;

	}

	return _longest;
}

bool Inventory::RemoveItem(Item* _item, const int _amount)
{
	if (inventory.empty() || !ContainItem(_item, _amount))
	{
		delete _item;
		return false;
	}
	
	int _index = 0;
	for (Slot* _slot : inventory)
	{
		if (_slot->item->GetName() == _item->GetName())
		{
			_slot->itemAmount -= _amount;
			if (_slot->itemAmount <= 0)
			{
				inventory.erase(inventory.begin() + _index);
				delete _slot;
			}
			delete _item;
			return true;
		}
		_index++;
	}
	delete _item;
	return false;
}

void Inventory::DisplayInventory()
{
	vector<vector<string>> _elements; // affichage complet

	const int _itemsPerLine = 5;
	const int _lines = 5; // nombre de ligne par item
	const int _longestName = GetLongestName();
	
	for (Slot* _slot : inventory)
	{
		_elements.push_back(_slot->item->GetDisplay(_longestName,_slot->GetDisplayAmount())); // tous les items
	}

	const int _size = static_cast<int>(_elements.size()); // nombre d'affichage

	int _offset = 0;
	do {
		for (int _index = 0; _index < _lines; _index++) // pour chaque ligne
		{
			for (int _index2 = _offset; _index2 < _offset + _itemsPerLine; _index2++) // de chaque item
			{
				if (_index2 >= _size) continue;
				cout << _elements[_index2][_index]; // afficher la ligne de l'item
			}
			cout << endl;
		}
		_offset += _itemsPerLine;
	} while (_offset <= _size);
}
