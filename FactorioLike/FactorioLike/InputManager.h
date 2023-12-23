#pragma once
#include "Singleton.h"

#include <string>
#include <map>
#include <conio.h>
#include <vector>
#include <functional>

using namespace std;

class InputManager : public Singleton<InputManager> {
map<vector<char>,function<void()>> keybinds;

public:
	InputManager();

private:
	function<void()> FindActions(const char _charactere);
	void ExcuteActions(const char _charactere);

public:
	void AddKeybind(const vector<char>& _keys, const function<void()>& _callback);
	void Tick();
};