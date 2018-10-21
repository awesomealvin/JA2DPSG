#pragma once
#include "Weapon.h"
class Melee :
	public Weapon
{
public:
	Melee();
	~Melee();

	EntityTypes GetType() const;

};

