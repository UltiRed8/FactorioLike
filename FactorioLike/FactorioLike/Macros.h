#pragma once

#include <random>

using namespace std;

static int RandomInRange(const int _max, const int _min = 0) {
	random_device _rd;
	mt19937 _seed(_rd());
	uniform_int_distribution<int> _distribution(_min, _max);
	return _distribution(_seed);
}