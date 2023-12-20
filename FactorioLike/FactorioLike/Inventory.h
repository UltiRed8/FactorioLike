#pragma once
#include "Item.h"
#include <vector>

using namespace std;

struct Slot
{
	Item* item = nullptr;
	int itemAmount = 0;


public:
	string GetDisplayAmount() const
	{
		return itemAmount > 99 ? "+99" : to_string(itemAmount);
	}
public:
	Slot(Item* _item, int _itemAmount)
	{
		item = _item;
		itemAmount = _itemAmount;
	}
public:
	~Slot()
	{
		delete item;
	}
};

class Inventory
{
	int maxItem;
	vector<Slot*> inventory;

public:
	Inventory();
	~Inventory();

public:
	bool AddItem(Item* _item,const int _amount);
	bool RemoveItem(Item* _item, const int _amount);
	void DisplayInventory();
private:
	bool ContainItem(Item* _item, const int _amount);
	int GetLongestName();
};

