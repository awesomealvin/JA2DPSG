#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include "entity.h"

//class BackBuffer;

class Particle :
	public Entity
{
public:
	Particle();
	~Particle();

	bool Initialise(Sprite* sprite, float minAliveTime, float maxAliveTime);
	void Revive(Vector2 position);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	float m_aliveTime;

protected:
	float m_minAliveTime;
	float m_maxAliveTime;
	float m_currentAliveTime;
	

};

#endif

