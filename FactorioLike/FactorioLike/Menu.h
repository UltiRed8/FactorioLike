#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "Colors.h"

using namespace std;

struct Button {
	string text;
	function<void()> callback;

public:
	Button(const string& _text, const function<void()>& _callback)
	{
		text = _text;
		callback = _callback;
	}

public:
	void Execute()
	{
		if (callback) callback();
	}
};

class Menu {
	string menuName;
	int selectedIndex;
	vector<Button> buttons;

public:
	Menu(const string& _name, const vector<Button>& _options);

private:
	void Display() const;

public:
	void ChangeSelected(const int _direction);
};

