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
	vector<Type> LoadConfig(const string& _path)
	{
		ifstream _stream = ifstream(CONFIGS + _path);
		if (!_stream)throw exception(("Le fichier de config " + _path + " n'a pas été trouvé").data());
		vector<Type> _list;
		string _line;
		vector<string> _values;

		while (getline(_stream,_line,':'))
		{
			_values.push_back(_line);
			//_list.push_back(Type(_type , _name));
		}
		return _list;
	}

};

