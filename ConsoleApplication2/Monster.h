#pragma once
#include <string>
using namespace std;

class Monster
{
public:
	Monster(string name);
	string getName();
	virtual void sayName();

protected:
	string name;
};

