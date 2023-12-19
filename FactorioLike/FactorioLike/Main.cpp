#include "GameManager.h"
#include "InputManager.h"
void Move(const int _deltaX,const int _deltaY)
{
	
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

	
	InputManager _input;


	_input.AddKeybind({'z'}, [&]() {Move(1,0); });
	_input.AddKeybind({'s'}, [&]() {Move(0,1); });
	_input.AddKeybind({'d'}, [&]() {Move(-1,0); });
	_input.AddKeybind({'q'}, [&]() {Move(0,-1); });

	do
	{
	_input.Tick();

	} while (true);

	return 0;
}
