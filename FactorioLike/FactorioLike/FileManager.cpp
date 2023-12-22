#include "FileManager.h"

string FileManager::GetLineStartingWithInConfig(const string& _startWith, const string& _path) {
    ifstream _stream = ifstream(CONFIGS + _path);
    if (!_stream) throw exception(("Le fichier de config " + _path + " n'a pas été trouvé").data());
    string _line;
    while (getline(_stream, _line))
    {
        if (_line.rfind(_startWith, 0))
        {
            return _line;
        }
    }
    return "";
}
