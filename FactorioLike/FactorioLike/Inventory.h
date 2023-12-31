#pragma once

#include <vector>

#include "Item.h"
#include "Location.h"
#include "Colors.h"

using namespace std;

struct Slot {
	Item* item = nullptr;
	int itemAmount = 0;


public:
	string GetDisplayAmount() const {
		return itemAmount > 99 ? "+99" : to_string(itemAmount);
	}
public:
	Slot(Item* _item, int _itemAmount) {
		item = _item;
		itemAmount = _itemAmount;
	}
	~Slot() {
		delete item;
	}
};

class Inventory {
	int itemsPerLine;
	int maxItem;
	int slotsUsed;
	vector<Slot*> inventory;
	Location cursorLocation;

public:
	Inventory();
	~Inventory();

private:
	int GetLongestName();

public:
	bool ContainItem(const string& _itemID, const int _amount);
	bool AddItem(Item* _item,const int _amount);
	bool RemoveItem(Item* _item, const int _amount);
	void DisplayInventory();
	void MoveCursor(const Location& _deltaLoc);
};