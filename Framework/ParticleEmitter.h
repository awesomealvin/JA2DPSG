#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include "Vector2.h"

class Particle;
class BackBuffer;
class Sprite;

class ParticleEmitter
{
public:
	static ParticleEmitter& GetInstance();
	~ParticleEmitter();
	static void DestroyInstance();

	bool Initialise(BackBuffer& backBuffer);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SpawnBloodExplosion(Vector2 position, int minAmount, int maxAmount);
	void SpawnMuzzleFlash(Vector2 position, int angle);
private:
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& particleEmitter);
	ParticleEmitter& operator=(const ParticleEmitter& particleEmitter);

protected:
	static ParticleEmitter* sm_pInstance;

	void CreateBloodParticles(BackBuffer& backBuffer);
	const int BLOOD_SIZE;
	const float BLOOD_MIN_ALIVE_TIME;
	const float BLOOD_MAX_ALIVE_TIME;
	Particle* m_pBloodParticles;
	Sprite** m_pBloodSprites;

	void CreateMuzzleParticles(BackBuffer& backbuffer);
	const int MUZZLE_SIZE;
	const float MUZZLE_MIN_ALIVE_TIME;
	const float MUZZLE_MAX_ALIVE_TIME;
	Particle* m_pMuzzleParticles;
	Sprite* m_pMuzzleSprite;

protected:

	template <class T>
	void ProcessEntity(T* objectArray, int size, float deltaTime)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!objectArray[i].IsDead())
			{
				objectArray[i].Process(deltaTime);
			}
		}
	}

	template <class T>
	void DrawEntity(T* objectArray, int size, BackBuffer& backBuffer)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!objectArray[i].IsDead())
			{
				objectArray[i].Draw(backBuffer);
			}
		}
	}
};

#endif
