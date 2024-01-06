#pragma once

#include <string>

using namespace std;

class Saveable
{

public:
	virtual void Load(const string& _loadLine) = 0;
	virtual string GetSaveLine() const = 0;
};