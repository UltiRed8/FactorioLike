#include "GameManager.h"
#include "InputManager.h"
void Move(const int _deltaX,const int _deltaY)
{
	cout << "moved" << endl;
}

int main()
{

	// map 250*250
	// viewport 26*26
	// player ZQSD | arrows
	// inventory E TAB I (25 => stacks illimités)
	// sauvegarde
	// chargement
	// 3 slots de save
	// ressources
	// machines (miner, smelter, foundry, constructor)

	GameManager::GetInstance().Start();

	return 0;
}
