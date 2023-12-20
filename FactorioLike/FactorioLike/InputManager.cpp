#include "InputManager.h"

void InputManager::AddKeybind(const vector<char>& _keys, const function<void()>& _callback)
{
    keybinds[_keys] = _callback;
}

function<void()> InputManager::FindActions(const char _charactere)
{
    map<vector<char>,function<void()>>::iterator _iterator = keybinds.begin();
    for (;_iterator != keybinds.end();_iterator++)
    {
        for (const char _char : _iterator->first)
        {
            if (toupper(_char) == toupper(_charactere))
            {
                return _iterator->second;
            }
        }
    }
    return function<void()>();
}

void InputManager::ExcuteActions(const char _charactere)
{
    function<void()> _callback = FindActions(_charactere);
    if (_callback) _callback();
}

void InputManager::Tick()
{
    char _char;

    while (_kbhit())
    {
        _char = _getch();
        ExcuteActions(_char);
    }
}