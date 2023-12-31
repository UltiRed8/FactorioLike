#include "Item.h"

Item::Item()
{
	name = "Unkown";
    id = "Unkown";
}

Item::Item(const string& _name, const string& _id)
{
	name = _name;
    id = _id;
}

vector<string> Item::GetDisplay(const int _targetLength, const string& _count) const
{
    vector<string> _list;
    string _line = "";

    // première ligne
    int _lenght = _targetLength + 4;
    for (int _i = 0; _i < _lenght; _i++) _line += "#";
    _line += " ";
    _list.push_back(_line);
    // ==================

    // deuxième ligne
    _line = "#";
    int _value = static_cast<const int>(((_lenght - 2) - name.length()));
    for (int _i = 0; _i < static_cast<const int>(ceil(_value / 2)); _i++) {
        _line += " ";
    }
    _line += name;
    if (_value % 2 == 1) _line += " ";
    for (int _i = 0; _i < static_cast<const int>(floor(_value / 2)); _i++) {
        _line += " ";
    }

    _line += "# ";
    _list.push_back(_line);
    // ==================

    // troisième ligne
    _line = "#";
    _value = static_cast<const int>(((_lenght - 2) - _count.length()));
    for (int _i = 0; _i < static_cast<const int>(ceil(_value / 2)); _i++) {
        _line += " ";
    }
    _line += _count;
    if (_value % 2 == 1) _line += " ";
    for (int _i = 0; _i < static_cast<const int>(floor(_value / 2)); _i++) {
        _line += " ";
    }
  
    _line += "# ";
    _list.push_back(_line);
    // ==================

    // quatrième ligne
    _list.push_back(_list[0]);
    // ==================

    _list.push_back("");

    return _list;
	
}
