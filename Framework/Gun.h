#ifndef __GUN_H__
#define __GUN_H__

#include "Weapon.h"

class Gun :
	public Weapon
{
public:
	Gun();
	~Gun();

	void Process(float deltaTime);

	enum FiringMode
	{
		SINGLE, BURST, AUTOMATIC
	};

protected:
	FiringMode m_firingMode;
	int m_ammoCount;
	float m_firingDelay;
	float m_accuracy;

};

#endif

