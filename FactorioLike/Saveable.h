#pragma once

#include <string>

using namespace std;

class Saveable
{

public:
	virtual void Load(const vector<string>& _list) = 0;
	virtual string GetSaveLine() const = 0;
};