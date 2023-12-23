#include "Map.h"
#include "Player.h"

Map::Map(const int _size, Player* _player) {
	player = _player;
	size = _size;
	viewDistance = 8; // TODO a changer en version finale
	Init();
	Generate();
}

void Map::Init() {
	grid.resize(size, vector<Element*>(size));
	const int _center = static_cast<const int>(size / 2);
	player->SetLocation({ _center, _center });
	grid[_center][_center] = player;
}

bool Map::IsEmptySpace(const Location& _location) const {
	if (!IsInRange(_location)) return false;
	return !grid[_location.posX][_location.posY];
}

vector<vector<Element*>> Map::GetViewport(const Location& _center) {
	vector<vector<Element*>> _viewport;
	vector<Element*> _line;
	for (int _x = viewDistance*-1; _x <= viewDistance; _x++) {
		for (int _y = viewDistance*-1; _y <= viewDistance; _y++) { {
				if (!IsInRange({ _center.posX + _x, _center.posY + _y })) continue;
				_line.push_back(grid[_center.posX + _x][_center.posY + _y]);
			}
		}
		_viewport.push_back(_line);
		_line.clear();
	}
	return _viewport;
}

void Map::Display() {
	vector<vector<Element*>> _viewport = GetViewport(player->GetLocation());
	const int _sizeX = static_cast<const int>(_viewport.size());
	for (int _x = 0; _x < _sizeX; _x++) {
		const int _sizeY = static_cast<const int>(_viewport[_x].size());
		for (int _y = 0; _y < _sizeY; _y++) {
			if (!_viewport[_x][_y]) cout << ". ";
			else cout << _viewport[_x][_y] << " ";
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
	try {
		_settings = FileManager::GetInstance().ConstructElementsFromConfig<GenerationSetting>("Generation.txt");
	} catch (const std::exception& _error) {
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
		NR_LEGENDARY
	};
	_targetLocation.Random(0, size - 1);
	for (GenerationSetting _setting : _settings) {
		while (!IsEmptySpace(_targetLocation)) _targetLocation.Random(0, size - 1);
		RessourceNode* _node = new RessourceNode(_rarities[RandomInRange(_size)], _setting.type);
		_node->SetLocation(_targetLocation);
		grid[_targetLocation.posX][_targetLocation.posY] = _node;
	}
}
