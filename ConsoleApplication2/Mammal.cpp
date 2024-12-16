#include "Mammal.h"
#include "Log.h"

Mammal::Mammal(string name) : Monster(name)
{
}

void Mammal::sayName()
{
	Log("OMG MY NAME IS " + name);
}
