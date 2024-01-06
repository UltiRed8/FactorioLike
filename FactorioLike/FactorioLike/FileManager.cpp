#include "FileManager.h"
#include "Player.h"

string FileManager::GetLineStartingWithInConfig(const string& _startWith, const string& _path)
{
    ifstream _stream = ifstream(CONFIGS + _path);
    if (!_stream) throw exception(("Le fichier de config " + _path + " n'a pas été trouvé").data());
    string _line;
    while (getline(_stream, _line))
    {
        if (!_line.rfind(_startWith, 0))
        {
            return _line;
        }
    }
    return "";
}

FileManager::FileManager()
{
    saveName = "Unknown";
}

void FileManager::SaveMap(const vector<vector<Element*>>& _map)
{
    ofstream _stream(SAVESLOT + saveName + ".map");
    if (!_stream)
    {
        string _error = "Erreur lors de la création de la sauvegarde MAP " + saveName + " !";
        throw exception(_error.c_str());
    }
    for (const vector<Element*> _line : _map)
    {
        for (Element* _element : _line)
        {
            if (!_element) continue;
            Saveable* _saveable = dynamic_cast<Saveable*>(_element);
            if (!_saveable) continue;
            _stream << _saveable->GetSaveLine() << endl;
        }
    }
}

void FileManager::SaveInventory(const Inventory& _inventory)
{
    ofstream _stream(SAVESLOT + saveName + ".inventory");
    if (!_stream)
    {
        string _error = "Erreur lors de la création de la sauvegarde INVENTORY " + saveName + " !";
        throw exception(_error.c_str());
    }
    _stream << _inventory.GetSaveLine() << endl;
}


void FileManager::SaveGame(const string& _saveName, Map* _map)
{
    saveName = _saveName;
    SaveMap(_map->GetGrid());
    SaveInventory(_map->GetPlayer()->GetInventory());
}

void FileManager::LoadGame(const string& _saveName, Map* _map)
{
    saveName = _saveName;
    LoadMap(_map);
    LoadInventory(_map->GetPlayer()->GetInventory());
}

void FileManager::LoadMap(Map* _map)
{
    ifstream _stream(SAVESLOT + saveName + ".map");
    if (!_stream)
    {
        string _error = "Erreur lors du chargement de la sauvegarde MAP " + saveName + " !";
        throw exception(_error.c_str());
    }
    string _line;
    vector<vector<Element*>>& _grid = _map->GetGrid();
    while (getline(_stream, _line))
    {
        vector<string> _currentList = LineToParts(_line);
        if (_currentList[0] == "RessourceNode") _grid[stoi(_currentList[1])][stoi(_currentList[2])] = new RessourceNode(_currentList);
        else if (_currentList[0] == "Player")
        {
            Player* _player = _map->GetPlayer();
            _player->Load(_currentList);
            _map->TeleportPlayer({ stoi(_currentList[1]), stoi(_currentList[2])});
        }
    }
}

void FileManager::LoadInventory(Inventory& _inventory)
{
    ifstream _stream(SAVESLOT + saveName + ".inventory");
    if (!_stream)
    {
        string _error = "Erreur lors du chargement de la sauvegarde INVENTORY " + saveName + " !";
        throw exception(_error.c_str());
    }
    string _line;
    while (getline(_stream, _line))
    {
        if (_line.empty()) continue;
        vector<string> _currentList = LineToParts(_line);
        _inventory.AddItem(new Item(_currentList[0]), stoi(_currentList[1]));
    }
}

vector<string> FileManager::LineToParts(string _line)
{
    vector<string> _list = vector<string>();
    string _word;
    while (_line.find(':') != string::npos)
    {
        _word = _line.substr(0, _line.find_first_of(':'));
        _line = _line.substr(_line.find_first_of(':') + 1, _line.length());
        _list.push_back(_word);
    }
    _list.push_back(_line);
    return _list;
}

//vector<vector<Element*>> FileManager::LoadGame(const string& _path)
//{
//
//
//
//    /*vector<vector<Element*>> _grid;
//
//    ifstream _stream(_path);
//
//    if (!_stream)
//    {
//        throw exception("Erreur lors de l'ouverture du fichier ");
//        _grid = vector<vector<Element*>>();
//        return _grid;
//    }
//
//    string _line;
//    
//    while (getline(_stream,_line))
//    {
//        vector<Element*> _store;
//        for (char _sign : _line)
//        {
//            Element* _element = CreateElementFromSign(_sign);
//        }
//        _grid.push_back(_store);
//    }
//    return _grid;*/
//    throw exception("rip");
//    return vector<vector<Element*>>();
//}



//Element* FileManager::CreateElementFromSign(const char _sign)
//{
//    Element* _newElement = nullptr;
//    //switch (_sign)
//    //{
//    //case 'P':
//    //    _newElement = new Player(); ==========> /!\ Le joueur est créé automatiquement lors de la création de la map, il faut juste charger sa position /!\
//    //    break;
//    //case 'R':
//    //    _newElement = new RessourceNode();
//    //default:
//    //    _newElement = nullptr;
//    //    break;
//    //}
//    return _newElement;
//}