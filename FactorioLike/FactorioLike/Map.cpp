#include "Map.h"

Map::Map(const int _size)
{
	size = _size;
	viewDistance = 4;
	Init();
	Generate();
}

void Map::Init()
{
	grid.resize(size, vector<Element*>(size));
}

vector<vector<Element*>> Map::GetViewport(const Location& _center)
{
	vector<vector<Element*>> _viewport;
	vector<Element*> _line;
	for (int _x = viewDistance*-1; _x < viewDistance+1; _x++)
	{
		for (int _y = viewDistance*-1; _y < viewDistance+1; _y++)
		{
			if (IsInRange({ _center._posX + _x, _center._posY + _y }))
			{
				_line.push_back(grid[_center._posX + _x][_center._posY + _y]);
			}
		}
		_viewport.push_back(_line);
		_line.clear();
	}
	return _viewport;
}

void Map::Display()
{
	vector<vector<Element*>> _viewport = GetViewport({ 7, 7 });
	for (int _x = 0; _x < viewDistance*2+1; _x++)
	{
		for (int _y = 0; _y < viewDistance*2+1; _y++)
		{
			if (IsInRange({ _x, _y }))
			{
				if (!_viewport[_x][_y]) cout << ". ";
				else cout << _viewport[_x][_y] << " ";
			}
		}
		cout << endl;
	}
}

bool Map::IsInRange(const Location& _location) const
{
	return (_location._posX >= 0 && _location._posY >= 0) && (_location._posX < size && _location._posY < size);
}

void Map::Generate()
{
	for (int _x = 0; _x < size; _x++)
	{
		for (int _y = 0; _y < size; _y++)
		{
			// TODO
		}
	}
}
