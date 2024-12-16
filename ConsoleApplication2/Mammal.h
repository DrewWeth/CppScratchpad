#pragma once
#include "Monster.h"

class Mammal :
    public Monster
{
public:
    Mammal(string name);

    void sayName();
};

