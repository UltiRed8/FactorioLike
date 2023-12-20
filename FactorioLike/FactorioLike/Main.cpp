#include "GameManager.h"
#include "InputManager.h"
#include "Player.h"

int main()
{

	locale::global(locale(""));

	// map 250*250
	// viewport 26*26
	// player ZQSD | arrows
	// inventory E TAB I (25 => stacks illimités)
	// sauvegarde
	// chargement
	// 3 slots de save
	// ressources
	// machines (miner, smelter, foundry, constructor)

	// bois
	// établi
	// batons
	// pioche bois
	// epée bois
	// 
	// pierre
	// charbon
	// pioche pierre
	// epée pierre
	// 
	// four
	// fer
	// batons de fer
	// pioche fer
	// mineur automatique
	// smelteur automatique
	// crafteur automatique
	//
	// epée lourde en fer

	Player* _player = new Player();
	_player->DisplayStatistics(true);
	do
	{
		InputManager::GetInstance().Tick();
	} while (true);
	delete _player;
	return 0;

	GameManager::GetInstance().Start();

	return 0;
}