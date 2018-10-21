#ifndef __OBJECTPOOL_H__
#define __OBJECTPOOL_H__

#include "EntityTypes.h"
#include "logmanager.h"
#include "entity.h"
#include <string>

class Ball;
class Entity;
class Box;
class Bullet;
class Pistol;
class Platform;
class BackBuffer;
class b2World;
class Character;
class Enemy;
class EnemyDeathParticle;
class EnemyHeadParticle;
class BloodExplosion;

class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();
	static ObjectPool& GetInstance();

	void Initialise(BackBuffer* backBuffer, b2World* world);

	void Draw(BackBuffer& backBuffer);
	void Process(float deltaTime);

	Entity* GetEntity(EntityTypes entityType);

	Bullet* GetBullet();
	Platform* GetPlatform();
	Platform* GetWall();
	Pistol* GetPistol();
	Enemy* GetEnemy();

	EnemyDeathParticle* GetEnemyTopLeftDeathParticle();
	EnemyDeathParticle* GetEnemyTopRightDeathParticle();
	EnemyDeathParticle* GetEnemyBottomDeathParticle();
	EnemyHeadParticle* GetEnemyHeadParticle();

	BloodExplosion* GetBloodExplosion();

	void SetAllDead();


	static void DestroyInstance();

	template <class T>
	T* GetDeadEntity(T** objectArray, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			if (objectArray[i]->IsDead())
			{
				objectArray[i]->m_dead = false;
				return objectArray[i];
			}
		}

		return 0;
	}	

	template <class T>
	void DrawEntity(T** objectArray, int size, BackBuffer& backBuffer)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!objectArray[i]->IsDead() && !objectArray[i]->ToTransformBody())
			{
				objectArray[i]->Draw(backBuffer);
			}
		}

	}

	template <class T>
	T** CreateEntityPool(int size, const char* spriteLocation)
	{
		T** objectArray = new T*[size];

		Sprite* sprite = m_backBuffer->CreateSprite(spriteLocation);

		for (int i = 0; i < size; ++i) {

			objectArray[i] = new T();
			objectArray[i]->Initialise(sprite);
			objectArray[i]->InitialiseBody(m_world, Vector2(300, 300));
			objectArray[i]->SetDead(true);
		}
		//objectArray[0]->SetDead(false);

		return objectArray;
	}

	template <class T>
	T** CreateAnimatedEntityPool(int size, const char* spriteLocation, int frameHeight, int frameWidth)
	{
		T** objectArray = new T*[size];


		for (int i = 0; i < size; ++i) {
			AnimatedSprite* animatedSprite = m_backBuffer->CreateAnimatedSprite(spriteLocation);

			objectArray[i] = new T();
			objectArray[i]->Initialise(animatedSprite, frameHeight, frameWidth);
			objectArray[i]->m_dead = true;
		}
		//objectArray[0]->SetDead(false);

		return objectArray;
	}

	template <class T>
	void ProcessEntity(T** objectArray, int size, float deltaTime)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!objectArray[i]->IsDead() || objectArray[i]->ToSetDead() || objectArray[i]->ToTransformBody())
			{
				objectArray[i]->Process(deltaTime);
			}
		}
	}

	template <class T>
	void DeleteEntity(T** objectArray, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			if (i == size - 1)
			{
				objectArray[i]->DestroySprite();
			}


			delete objectArray[i];
			objectArray[i] = 0;


		}

		delete[] objectArray;
		objectArray = 0;
	}

	template <class T>
	void DisableEntity(T** objectArray, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			if (!objectArray[i]->IsDead())
			{
				objectArray[i]->SetDead(true);
				objectArray[i]->SetPosition(Vector2(-100, -100));
			}
		}
	}

private:
	ObjectPool(const ObjectPool& objectPool);
	ObjectPool& operator=(const ObjectPool& objectPool);

protected:
	void CreateBallPool();
	void CreateBoxPool();
	void CreateBulletPool();
	void CreatePistolPool();
	void CreatePlatformPool();
	void CreateWallPool();
	void CreateEnemyPool();

protected:
	BackBuffer* m_backBuffer;
	b2World* m_world;

	Ball** m_ballPool;
	const int BALL_SIZE;

	Box** m_boxPool;
	const int BOX_SIZE;

	Bullet** m_bulletPool;
	const int BULLET_SIZE;

	Pistol** m_pistolPool;
	const int PISTOL_SIZE;

	Platform** m_platformPool;
	const int PLATFORM_SIZE;

	Platform** m_wallPool;
	const int WALL_SIZE;

	Enemy** m_enemyPool;
	const int ENEMY_SIZE;

	EnemyDeathParticle** m_enemyTopLeftDeathParticle;
	const int ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE;

	EnemyDeathParticle** m_enemyTopRightDeathParticle;
	const int ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE;

	EnemyDeathParticle** m_enemyBottomDeathParticle;
	const int ENEMY_BOTTOM_DEATH_PARTICLE_SIZE;

	EnemyHeadParticle** m_enemyHeadPool;
	const int ENEMY_HEAD_SIZE;

	BloodExplosion** m_bloodExplosionPool;
	const int BLOOD_EXPLOSION_SIZE;

	static ObjectPool* sm_pInstance;

};

#endif

