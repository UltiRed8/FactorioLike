#pragma once

#include <random>
#include <fcntl.h>
#include <io.h>
#include <iostream>

using namespace std;

#define SPECIALCHAR(x) int _temp = _setmode(_fileno(stdout), _O_U16TEXT); \
						std::wcout << x; \
						_temp = _setmode(_fileno(stdout), _O_TEXT);


static int RandomInRange(const int _max, const int _min = 0)
{
	random_device _rd;
	mt19937 _seed(_rd());
	uniform_int_distribution<int> _distribution(_min, _max);
	return _distribution(_seed);
}

static vector<string> SplitString(string _line, const char _divider)
{
	vector<string> _results;
	string _word;
	while (_line.find(_divider) != string::npos)
	{
		_word = _line.substr(0, _line.find_first_of(_divider));
		_line = _line.substr(_line.find_first_of(_divider) + 1, _line.length());
		_results.push_back(_word);
	}
	_results.push_back(_line);
	return _results;
}