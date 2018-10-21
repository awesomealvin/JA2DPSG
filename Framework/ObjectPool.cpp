#include "ObjectPool.h"

#include "backbuffer.h"
#include "Pistol.h"
#include "Bullet.h"
#include "Platform.h"
#include "EntityTypes.h"
#include "entity.h"
#include "Enemy.h"
#include "Character.h"
#include "EnemyDeathParticle.h"
#include "EnemyHeadParticle.h"
#include "BloodExplosion.h"

ObjectPool* ObjectPool::sm_pInstance = 0;

ObjectPool::ObjectPool() 
	: BALL_SIZE(32)
	, BOX_SIZE(32)
	, BULLET_SIZE(128)
	, PISTOL_SIZE(32)
	, PLATFORM_SIZE(64)
	, WALL_SIZE(64)
	, ENEMY_SIZE(32)
	, ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE(24)
	, ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE(24)
	, ENEMY_BOTTOM_DEATH_PARTICLE_SIZE(48)
	, ENEMY_HEAD_SIZE(32)
	, BLOOD_EXPLOSION_SIZE(16)
{

}

ObjectPool::~ObjectPool()
{
	DeleteEntity(m_pistolPool, PISTOL_SIZE);
	DeleteEntity(m_bulletPool, BULLET_SIZE);
	DeleteEntity(m_platformPool, PLATFORM_SIZE);
	DeleteEntity(m_wallPool, WALL_SIZE);
	DeleteEntity(m_enemyPool, ENEMY_SIZE);
	DeleteEntity(m_enemyTopLeftDeathParticle, ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE);
	DeleteEntity(m_enemyTopRightDeathParticle, ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE);
	DeleteEntity(m_enemyBottomDeathParticle, ENEMY_BOTTOM_DEATH_PARTICLE_SIZE);
	DeleteEntity(m_enemyHeadPool, ENEMY_HEAD_SIZE);
	DeleteEntity(m_bloodExplosionPool, BLOOD_EXPLOSION_SIZE);

}

ObjectPool & ObjectPool::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new ObjectPool();
	}

	return (*sm_pInstance);
}

void ObjectPool::Initialise(BackBuffer* backBuffer, b2World* world)
{
	m_backBuffer = backBuffer;
	m_world = world;
	CreatePlatformPool();

	CreatePistolPool();
	//CreateBulletPool();
	m_bulletPool = CreateEntityPool<Bullet>(BULLET_SIZE, "..\\bin\\assets\\bullet.png");
	CreateWallPool();
	CreateEnemyPool();
	//m_enemyPool = CreateEntityPool<Enemy>(ENEMY_SIZE, "..\\bin\\assets\\enemy.png");

	//CreateEntityPool<EnemyDeathParticle>(50, "HELO");
	m_enemyTopLeftDeathParticle = CreateEntityPool<EnemyDeathParticle>(ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE, "..\\bin\\assets\\enemy_piece_1.png");
	m_enemyTopRightDeathParticle = CreateEntityPool<EnemyDeathParticle>(ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE, "..\\bin\\assets\\enemy_piece_2.png");
	m_enemyBottomDeathParticle = CreateEntityPool<EnemyDeathParticle>(ENEMY_BOTTOM_DEATH_PARTICLE_SIZE, "..\\bin\\assets\\enemy_piece_3.png");

	m_enemyHeadPool = CreateEntityPool<EnemyHeadParticle>(ENEMY_HEAD_SIZE, "..\\bin\\assets\\enemy_head.png");

	m_bloodExplosionPool = CreateAnimatedEntityPool<BloodExplosion>(
		BLOOD_EXPLOSION_SIZE, "..\\bin\\assets\\blood_explosion.png", 64, 64);
}

void ObjectPool::Draw(BackBuffer& backBuffer)
{
	DrawEntity(m_pistolPool, PISTOL_SIZE, backBuffer);
	DrawEntity(m_bulletPool, BULLET_SIZE, backBuffer);
	DrawEntity(m_platformPool, PLATFORM_SIZE, backBuffer);
	DrawEntity(m_wallPool, WALL_SIZE, backBuffer);
	DrawEntity(m_enemyPool, ENEMY_SIZE, backBuffer);

	DrawEntity(m_enemyTopLeftDeathParticle, ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE, backBuffer);
	DrawEntity(m_enemyTopRightDeathParticle, ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE, backBuffer);
	DrawEntity(m_enemyBottomDeathParticle, ENEMY_BOTTOM_DEATH_PARTICLE_SIZE, backBuffer);
	DrawEntity(m_enemyHeadPool, ENEMY_HEAD_SIZE, backBuffer);

	DrawEntity(m_bloodExplosionPool, BLOOD_EXPLOSION_SIZE, backBuffer);
}

void ObjectPool::Process(float deltaTime)
{
	ProcessEntity(m_pistolPool, PISTOL_SIZE, deltaTime);
	ProcessEntity(m_bulletPool, BULLET_SIZE, deltaTime);
	ProcessEntity(m_platformPool, PLATFORM_SIZE, deltaTime);
	ProcessEntity(m_wallPool, WALL_SIZE, deltaTime);
	ProcessEntity(m_enemyPool, ENEMY_SIZE, deltaTime);

	ProcessEntity(m_enemyTopLeftDeathParticle, ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE, deltaTime);
	ProcessEntity(m_enemyTopRightDeathParticle, ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE, deltaTime);
	ProcessEntity(m_enemyBottomDeathParticle, ENEMY_BOTTOM_DEATH_PARTICLE_SIZE, deltaTime);
	ProcessEntity(m_enemyHeadPool, ENEMY_HEAD_SIZE, deltaTime);
	
	ProcessEntity(m_bloodExplosionPool, BLOOD_EXPLOSION_SIZE, deltaTime);

}

Entity* ObjectPool::GetEntity(EntityTypes entityType)
{
	Entity* returnEntity;
	switch (entityType)
	{
	case EntityTypes::PLATFORM: returnEntity = GetPlatform();
		break;
	case EntityTypes::WALL: returnEntity = GetWall();
		break;
	case EntityTypes::PISTOL: returnEntity = GetPistol();
		break;
	case EntityTypes::ENEMIES: returnEntity = GetEnemy();
		break;
	default: returnEntity = GetPlatform();
		break;
	}

	return returnEntity;
}

Bullet * ObjectPool::GetBullet()
{
	Bullet* bullet = GetDeadEntity(m_bulletPool, BULLET_SIZE);
	return bullet;
}

Platform * ObjectPool::GetPlatform()
{

	return GetDeadEntity(m_platformPool, PLATFORM_SIZE);
}

Platform * ObjectPool::GetWall()
{
	return GetDeadEntity(m_wallPool, WALL_SIZE);
}

Pistol * ObjectPool::GetPistol()
{
	return GetDeadEntity(m_pistolPool, PISTOL_SIZE);
}

Enemy * ObjectPool::GetEnemy()
{
	return GetDeadEntity(m_enemyPool, ENEMY_SIZE);
}

EnemyDeathParticle * ObjectPool::GetEnemyTopLeftDeathParticle()
{
	return GetDeadEntity(m_enemyTopLeftDeathParticle, ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE);
}

EnemyDeathParticle * ObjectPool::GetEnemyTopRightDeathParticle()
{
	return GetDeadEntity(m_enemyTopRightDeathParticle, ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE);
}

EnemyDeathParticle * ObjectPool::GetEnemyBottomDeathParticle()
{
	return GetDeadEntity(m_enemyBottomDeathParticle, ENEMY_BOTTOM_DEATH_PARTICLE_SIZE);
}

EnemyHeadParticle * ObjectPool::GetEnemyHeadParticle()
{
	return GetDeadEntity(m_enemyHeadPool, ENEMY_HEAD_SIZE);
}

BloodExplosion * ObjectPool::GetBloodExplosion()
{
	return GetDeadEntity(m_bloodExplosionPool, BLOOD_EXPLOSION_SIZE);
}

void ObjectPool::SetAllDead()
{
	/*Bullet* GetBullet();
	Platform* GetPlatform();
	Platform* GetWall();
	Pistol* GetPistol();
	Enemy* GetEnemy();

	EnemyDeathParticle* GetEnemyTopLeftDeathParticle();
	EnemyDeathParticle* GetEnemyTopRightDeathParticle();
	EnemyDeathParticle* GetEnemyBottomDeathParticle();
	EnemyHeadParticle* GetEnemyHeadParticle();*/

	DisableEntity(m_bulletPool, BULLET_SIZE);
	DisableEntity(m_platformPool, PLATFORM_SIZE);
	DisableEntity(m_wallPool, WALL_SIZE);
	DisableEntity(m_pistolPool, PISTOL_SIZE);
	DisableEntity(m_enemyPool, ENEMY_SIZE);
	DisableEntity(m_enemyTopLeftDeathParticle, ENEMY_TOP_LEFT_DEATH_PARTICLE_SIZE);
	DisableEntity(m_enemyTopRightDeathParticle, ENEMY_TOP_RIGHT_DEATH_PARTICLE_SIZE);
	DisableEntity(m_enemyBottomDeathParticle, ENEMY_BOTTOM_DEATH_PARTICLE_SIZE);
	DisableEntity(m_enemyHeadPool, ENEMY_HEAD_SIZE);
}


void ObjectPool::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void ObjectPool::CreateBallPool()
{
}

void ObjectPool::CreateBoxPool()
{
}

void ObjectPool::CreateBulletPool()
{
	m_bulletPool = new Bullet*[BULLET_SIZE];
	Sprite* sprite = m_backBuffer->CreateSprite("..\\bin\\assets\\bullet.png");

	for (int i = 0; i < BULLET_SIZE; ++i)
	{
		m_bulletPool[i] = new Bullet();
		m_bulletPool[i]->Initialise(sprite);
		m_bulletPool[i]->InitialiseBody(m_world, Vector2(-100, -100));
		m_bulletPool[i]->SetDead(true);
	}
}

void ObjectPool::CreatePistolPool()
{
	m_pistolPool = new Pistol*[PISTOL_SIZE];
	Sprite* pistolSprite = m_backBuffer->CreateSprite("..\\bin\\assets\\pistol.png");

	for (int i = 0; i < PISTOL_SIZE; ++i) {

		m_pistolPool[i] = new Pistol();
		m_pistolPool[i]->Initialise(pistolSprite);
		m_pistolPool[i]->InitialiseBody(m_world, Vector2(300, 300));
		m_pistolPool[i]->SetDead(true);
	}
}

void ObjectPool::CreatePlatformPool()
{
	m_platformPool = new Platform*[PLATFORM_SIZE];
	Sprite* platformSprite = m_backBuffer->CreateSprite("..\\bin\\assets\\platform.png");

	for (int i = 0; i < PLATFORM_SIZE; ++i) {

		m_platformPool[i] = new Platform();
		m_platformPool[i]->Initialise(platformSprite);
		m_platformPool[i]->InitialiseBody(m_world, Vector2(-50, -50));
		m_platformPool[i]->SetDead(true);
	}
}

void ObjectPool::CreateWallPool()
{
	m_wallPool = new Platform*[WALL_SIZE];

	Sprite* sprite = m_backBuffer->CreateSprite("..\\bin\\assets\\wall.png");

	for (int i = 0; i < WALL_SIZE; ++i) {

		m_wallPool[i] = new Platform();
		m_wallPool[i]->Initialise(sprite);
		m_wallPool[i]->InitialiseBody(m_world, Vector2(-50, -50));
		m_wallPool[i]->SetDead(true);
	}
}

void ObjectPool::CreateEnemyPool()
{
	m_enemyPool = new Enemy*[ENEMY_SIZE];

	Sprite* sprite = m_backBuffer->CreateSprite("..\\bin\\assets\\enemy.png");

	for (int i = 0; i < ENEMY_SIZE; ++i) {

		m_enemyPool[i] = new Enemy();
		m_enemyPool[i]->Initialise(sprite);
		m_enemyPool[i]->InitialiseBody(m_world, Vector2(-50, -50));
		m_enemyPool[i]->SetDead(true);
	}
}


