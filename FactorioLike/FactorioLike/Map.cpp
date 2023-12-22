#include "Map.h"

Map::Map(const int _size) {
	size = _size;
	viewDistance = 4;
	Init();
	Generate();
}

void Map::Init() {
	grid.resize(size, vector<Element*>(size));
}

bool Map::IsEmptySpace(const Location& _location) const {
	if (!IsInRange(_location)) return false;
	return !grid[_location.posX][_location.posY];
}

vector<vector<Element*>> Map::GetViewport(const Location& _center) {
	vector<vector<Element*>> _viewport;
	vector<Element*> _line;
	for (int _x = viewDistance*-1; _x < viewDistance+1; _x++) {
		for (int _y = viewDistance*-1; _y < viewDistance+1; _y++) { {
				_line.push_back(grid[_center.posX + _x][_center.posY + _y]);
			}
		}
		_viewport.push_back(_line);
		_line.clear();
	}
	return _viewport;
}

void Map::Display() {
	vector<vector<Element*>> _viewport = GetViewport({ 7, 7 });
	for (int _x = 0; _x < viewDistance*2+1; _x++) {
		for (int _y = 0; _y < viewDistance*2+1; _y++) {
			if (IsInRange({ _x, _y })) {
				if (!_viewport[_x][_y]) cout << ". ";
				else cout << _viewport[_x][_y] << " ";
			}
		}
		cout << endl;
	}
}

bool Map::MoveElement(const Location& _defaultLocation, const Location& _newLocation) {
	if (!IsInRange(_defaultLocation)) return false;
	if (!IsEmptySpace(_newLocation)) return false;
	Element* _element = grid[_defaultLocation.posX][_defaultLocation.posY];
	grid[_defaultLocation.posX][_defaultLocation.posY] = grid[_newLocation.posX][_newLocation.posY];
	grid[_newLocation.posX][_newLocation.posY] = _element;
	return true;
}

bool Map::IsInRange(const Location& _location) const {
	return (_location.posX >= 0 && _location.posY >= 0) && (_location.posX < size && _location.posY < size);
}

void Map::Generate() {
	vector<GenerationSetting> _settings;
	try
	{
	_settings = FileManager::GetInstance().ConstructElementsFromConfig<GenerationSetting>("Generation.txt");
	}
	catch (const std::exception& _error)
	{
		cerr << _error.what();
	}

	Location _targetLocation;

	const int _size = 10;
	const NodeRarity _rarities[_size] = {
		NR_COMMUN,
		NR_COMMUN,
		NR_COMMUN,
		NR_COMMUN,
		NR_RARE,
		NR_RARE,
		NR_RARE,
		NR_EPIC,
		NR_EPIC,
		NR_LEGENDARY,
	};


	
	_targetLocation.Random(0, size - 1);
	for (GenerationSetting _setting : _settings)
	{
		while (!grid[_targetLocation.posX][_targetLocation.posY])
		{
			_targetLocation.Random(0, size - 1);
		}
		grid[_targetLocation.posX][_targetLocation.posY] = new RessourceNode(_rarities[RandomInRange(_size)], _setting.ressource.type);
	}
}
