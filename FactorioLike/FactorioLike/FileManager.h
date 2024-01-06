#pragma once
#include "Singleton.h"
#include "Colors.h"
#include <cstring>
#include <iostream>
#include "Element.h"
#include <vector>
#include <string>
#include <fstream>

class Map;
class Player;
class Inventory;

using namespace std;

#define CONFIGS "Ressources/Configs/"
#define SAVESLOT "Saves/"

class FileManager : public Singleton<FileManager>
{
    string saveName;

public:
    FileManager();

private:
    void SaveMap(const vector<vector<Element*>>& _map);
    void SaveInventory(const Inventory& _inventory);

public:
    template<typename Type>
    vector<Type> ConstructElementsFromConfig(const string& _path)
    {
        vector<Type> _list;
        ifstream _stream = ifstream(CONFIGS + _path);
        if (!_stream) throw exception(("Le fichier de config " + _path + " n'a pas été trouvé").data());
        string _line;
        while (getline(_stream, _line))
        {
            _list.push_back(Type(_line));
        }
        return _list;
    }

    string GetLineStartingWithInConfig(const string& _startWith, const string& _path);
    Element* CreateElementFromSign(const char _sign);

    void SaveGame(const string& _saveName, Map* _map);
    vector<vector<Element*>> LoadGame(const string& _path);
};