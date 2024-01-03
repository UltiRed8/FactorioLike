#include "Item.h"

Item::Item()
{
	name = "Unkown";
    id = "Unkown";
}

Item::Item(const string& _id)
{
    id = _id;
    GetNameFromConfig();
}

void Item::GetNameFromConfig()
{
    try
    {
        const string _line = FileManager::GetInstance()->GetLineStartingWithInConfig(id + ":", "Translations.txt");
        name = _line.substr(_line.find_first_of(":") + 1, _line.length());
    }
    catch (const exception _e)
    {
        name = "Unkown";
        cout << _e.what() << endl;
        system("PAUSE");
    }
}

vector<string> Item::GetInventoryDisplay(const int _targetLength, const string& _count) const
{
    vector<string> _list;
    string _line = "";
    int _lenght = _targetLength + 4;
    for (int _i = 0; _i < _lenght; _i++) _line += "#";
    _line += " ";
    _list.push_back(_line);
    _line = "#";
    int _value = static_cast<const int>(((_lenght - 2) - name.length()));
    for (int _i = 0; _i < static_cast<const int>(ceil(_value / 2)); _i++)
    {
        _line += " ";
    }
    _line += name;
    if (_value % 2 == 1) _line += " ";
    for (int _i = 0; _i < static_cast<const int>(floor(_value / 2)); _i++)
    {
        _line += " ";
    }
    _line += "# ";
    _list.push_back(_line);
    _line = "#";
    _value = static_cast<const int>(((_lenght - 2) - _count.length()));
    for (int _i = 0; _i < static_cast<const int>(ceil(_value / 2)); _i++)
    {
        _line += " ";
    }
    _line += _count;
    if (_value % 2 == 1) _line += " ";
    for (int _i = 0; _i < static_cast<const int>(floor(_value / 2)); _i++)
    {
        _line += " ";
    }
    _line += "# ";
    _list.push_back(_line);
    _list.push_back(_list[0]);
    _list.push_back("");
    return _list;
}