#ifndef __PISTOL_H__
#define __PISTOL_H__
#include "Gun.h"
class Pistol :
	public Gun
{
public:
	Pistol();
	~Pistol();

	void Process(float deltaTime);

};

#endif

