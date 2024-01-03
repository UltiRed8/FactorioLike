#include "FileManager.h"


string FileManager::GetLineStartingWithInConfig(const string& _startWith, const string& _path) {
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

void FileManager::SaveMap(const string& _path,vector<vector<Element*>> _grid)
{
    ofstream _stream(_path);

    if (!_stream) {
        throw exception("Erreur lors de l'ouverture du fichier ");
        return;
    }

    for (int _x = 0; _x < _grid.size(); _x++)
    {
        for (int _y = 0; _y < _grid.size(); _y++)
        {
            Element* _element = _grid[_x][_y];
            if (_element)
            {
                _stream << _element->GetSign();
                _stream << " ";
            } 
            else
            {
                _stream << ". ";
            }
        }
        _stream << endl;
    }
}

vector<vector<Element*>> FileManager::LoadMap(const string& _path)
{
    vector<vector<Element*>> _grid;

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
    return _grid;
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