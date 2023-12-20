#include "GameManager.h"
#include "Inventory.h"
#include "InputManager.h"

#include<fcntl.h>
#include <io.h>
#include <iostream>

int main()
{

	locale::global(locale(""));
	//_setmode(_fileno(stdout), _O_U8TEXT);
	//std::wcout << "\x1B[38;5;196m"L'\u2665' << std::endl;
	
	Inventory _inventory;
	_inventory.AddItem(new Item("pierre"), 4);
	_inventory.AddItem(new Item("Heavy"), 4);
	_inventory.AddItem(new Item("e"), 127);
	_inventory.AddItem(new Item("fer"), 4);
	_inventory.AddItem(new Item("pioche"), 4);
	_inventory.AddItem(new Item("hache"), 4);
	_inventory.AddItem(new Item("diams"), 4);
	_inventory.AddItem(new Item("nether"), 4);
	_inventory.AddItem(new Item("bronze"), 4);
	_inventory.AddItem(new Item("astral"), 4);
	_inventory.AddItem(new Item("111"), 4);
	_inventory.AddItem(new Item("121"), 4);
	_inventory.AddItem(new Item("131"), 4);
	_inventory.AddItem(new Item("141"), 4);
	_inventory.AddItem(new Item("151"), 4);
	_inventory.AddItem(new Item("161"), 4);
	_inventory.AddItem(new Item("171"), 4);
	_inventory.AddItem(new Item("181"), 4);
	_inventory.AddItem(new Item("191"), 4);
	_inventory.AddItem(new Item("201"), 4);
	_inventory.AddItem(new Item("211"), 4);
	_inventory.AddItem(new Item("221"), 4);
	_inventory.AddItem(new Item("231"), 4);
	_inventory.AddItem(new Item("241"), 4);
	
	_inventory.DisplayInventory();

	system("pause");
	system("cls");

	_inventory.RemoveItem(new Item("fer"), 4);

	_inventory.DisplayInventory();


	//_setmode(_fileno(stdout), _O_TEXT);
	//cout << "coucou" << endl;
	// map 250*250
	// viewport 26*26
	// player ZQSD | arrows
	// inventory E TAB I (25 => stacks illimités)
	// sauvegarde
	// chargement
	// 3 slots de save
	// ressources
	// machines (miner, smelter, foundry, constructor)

	//GameManager::GetInstance().Start();

	return 0;
}
