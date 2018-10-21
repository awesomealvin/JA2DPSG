#ifndef __BLOODEXPLOSION_H__
#define __BLOODEXPLOSION_H__
#include "entity.h"
class BloodExplosion :
	public Entity
{
public:
	BloodExplosion();
	~BloodExplosion();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	EntityTypes GetType() const;

	void DestroySprite();

	void StartAnimating();

};

#endif

