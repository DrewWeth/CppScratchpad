#include "Monster.h"
#include "Log.h"


Monster::Monster(string Name)
{
    name = Name;
}

std::string Monster::getName()
{
    return name;
}

void Monster::sayName()
{
    Log("My name is: " + name);
}
