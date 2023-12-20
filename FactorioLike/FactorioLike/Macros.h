#pragma once

#include <random>
#include <fcntl.h>
#include <io.h>
#include <iostream>

using namespace std;

#define SPECIALCHAR(x) int _temp = _setmode(_fileno(stdout), _O_U16TEXT); \
						std::wcout << x; \
						_temp = _setmode(_fileno(stdout), _O_TEXT);


static int RandomInRange(const int _max, const int _min = 0) {
	random_device _rd;
	mt19937 _seed(_rd());
	uniform_int_distribution<int> _distribution(_min, _max);
	return _distribution(_seed);
}