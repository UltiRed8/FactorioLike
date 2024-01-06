#include "Menu.h"

Menu::Menu(const string& _name, const vector<Button>& _options)
{
	menuName = _name;
	selectedIndex = 0;
	buttons = _options;
	Display();
}

void Menu::Display() const
{
	system("CLS");
	cout << "========" << menuName << "========" << endl;
	const int _amountOfButtons = static_cast<const int>(buttons.size());
	for (int _index = 0; _index < _amountOfButtons; _index++)
	{
		if (_index == selectedIndex) cout << LIME;
		cout << "> " << buttons[_index].text << COLORRESET << endl;
	}
	const int _titleLength = static_cast<const int>(menuName.length());
	for (int _index = 0; _index <= _titleLength; _index++)
	{
		cout << "=";
	}
	cout << "===============" << endl;
}

void Menu::ChangeSelected(const int _direction)
{
	selectedIndex += _direction;
	const int _amountOfButtons = static_cast<const int>(buttons.size());
	if (selectedIndex < 0) selectedIndex = _amountOfButtons-1;
	else if (selectedIndex >= _amountOfButtons) selectedIndex = 0;
	Display();
}
