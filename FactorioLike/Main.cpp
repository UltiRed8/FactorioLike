#include "GameManager.h"
#include "InputManager.h"
#include "Inventory.h"
#include "Player.h"
#include "Colors.h"

using namespace std;

template<typename Type>
Type GetInput(const string& _question)
{
	cout << _question;
	Type _result;
	cin >> _result;
	return _result;
}

int main()
{
	locale::global(locale(""));
	
	const string _save = GetInput<string>("Enter the name of the save that you want to use:\n> ");
	if (!_save.empty())
	{
		GameManager::GetInstance()->SetSaveName(_save);
		GameManager::GetInstance()->Start();
	}
	system("CLS");
	cout << "Goodbye!" << endl;

	return 0;
}