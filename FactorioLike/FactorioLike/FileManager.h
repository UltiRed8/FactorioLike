#pragma once
#include "Singleton.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#define CONFIGS "Ressources/Configs/"
#define SAVESLOT "Ressources/SaveSlots/"

class FileManager : public Singleton<FileManager>
{
    //LoadMap
    //LoadConfig
    //Save
public:
    template<typename Type>
    vector<Type> ConstructElementsFromConfig(const string& _path) {
        vector<Type> _list;
        ifstream _stream = ifstream(CONFIGS + _path);
        if (!_stream) throw exception(("Le fichier de config " + _path + " n'a pas été trouvé").data());
        string _line;
        while (getline(_stream, _line)) {
            _list.push_back(Type(_line));
        }
        return _list;
    }

    string GetLineStartingWithInConfig(const string& _startWith, const string& _path);
};