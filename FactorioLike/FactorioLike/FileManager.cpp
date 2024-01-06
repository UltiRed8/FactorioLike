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
            if (dynamic_cast<Entity*>(_element)) continue;
            _stream << _element->GetSaveableLine() << endl;
        }
    }
}

void FileManager::SavePlayer(Player* _player)
{
    ofstream _stream(SAVESLOT + saveName + ".player");
    if (!_stream)
    {
        string _error = "Erreur lors de la création de la sauvegarde PLAYER " + saveName + " !";
        throw exception(_error.c_str());
    }
    _stream << _player->GetSaveableLine() << endl;
}

void FileManager::SaveInventory(const Inventory& _inventory)
{
    ofstream _stream(SAVESLOT + saveName + ".inventory");
    if (!_stream)
    {
        string _error = "Erreur lors de la création de la sauvegarde INVENTORY " + saveName + " !";
        throw exception(_error.c_str());
    }
    _stream << _inventory.GetSaveableLine() << endl;
}


void FileManager::SaveGame(const string& _saveName, Map* _map)
{
    saveName = _saveName;
    SaveMap(_map->GetGrid());
    Player* _player = _map->GetPlayer();
    SavePlayer(_player);
    SaveInventory(_player->GetInventory());
}

vector<vector<Element*>> FileManager::LoadGame(const string& _path)
{
    /*vector<vector<Element*>> _grid;

    ifstream _stream(_path);

    if (!_stream)
    {
        throw exception("Erreur lors de l'ouverture du fichier ");
        _grid = vector<vector<Element*>>();
        return _grid;
    }

    string _line;
    
    while (getline(_stream,_line))
    {
        vector<Element*> _store;
        for (char _sign : _line)
        {
            Element* _element = CreateElementFromSign(_sign);
        }
        _grid.push_back(_store);
    }
    return _grid;*/
    throw exception("rip");
    return vector<vector<Element*>>();
}



Element* FileManager::CreateElementFromSign(const char _sign)
{
    Element* _newElement = nullptr;
    //switch (_sign)
    //{
    //case 'P':
    //    _newElement = new Player(); ==========> /!\ Le joueur est créé automatiquement lors de la création de la map, il faut juste charger sa position /!\
    //    break;
    //case 'R':
    //    _newElement = new RessourceNode();
    //default:
    //    _newElement = nullptr;
    //    break;
    //}
    return _newElement;
}