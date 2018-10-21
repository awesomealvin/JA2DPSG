#include "ParticleEmitter.h"

#include "Particle.h"
#include "sprite.h"
#include "backbuffer.h"
#include "MyUtility.h"
#include "logmanager.h"
#include <cstring>

ParticleEmitter* ParticleEmitter::sm_pInstance = 0;


ParticleEmitter::ParticleEmitter()
	: BLOOD_SIZE(384)
	, BLOOD_MIN_ALIVE_TIME(0.125f)
	, BLOOD_MAX_ALIVE_TIME(0.5f)
	, MUZZLE_SIZE(720)
	, MUZZLE_MIN_ALIVE_TIME(0.050f)
	, MUZZLE_MAX_ALIVE_TIME(0.125f)
{
}


ParticleEmitter & ParticleEmitter::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new ParticleEmitter();
	}

	return (*sm_pInstance);
}

ParticleEmitter::~ParticleEmitter()
{
	for (int i = 0; i < 3; ++i)
	{
		delete m_pBloodSprites[i];
		m_pBloodSprites[i] = 0;
	}
	delete[] m_pBloodSprites;
	m_pBloodSprites = 0;

	delete[] m_pBloodParticles;
	m_pBloodParticles = 0;

	delete m_pMuzzleSprite;
	m_pMuzzleSprite = 0;
	delete[] m_pMuzzleParticles;
}
void ParticleEmitter::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}


bool ParticleEmitter::Initialise(BackBuffer & backBuffer)
{
	CreateBloodParticles(backBuffer);
	CreateMuzzleParticles(backBuffer);
	return true;
}

void ParticleEmitter::Process(float deltaTime)
{
	ProcessEntity(m_pBloodParticles, BLOOD_SIZE, deltaTime);
	ProcessEntity(m_pMuzzleParticles, MUZZLE_SIZE, deltaTime);
}

void ParticleEmitter::Draw(BackBuffer & backBuffer)
{
	DrawEntity(m_pBloodParticles, BLOOD_SIZE, backBuffer);
	DrawEntity(m_pMuzzleParticles, MUZZLE_SIZE, backBuffer);
}

void ParticleEmitter::SpawnBloodExplosion(Vector2 position, int minAmount, int maxAmount)
{
	int particleAmount = MyUtility::RandomInt(minAmount, maxAmount);
	int particles = 0;

	for (int i = 0; i < BLOOD_SIZE && particles < particleAmount; ++i)
	{
		if (m_pBloodParticles[i].IsDead())
		{
			m_pBloodParticles[i].Revive(position);
			int angle = MyUtility::RandomInt(0, 360);
			Vector2 velocity = MyUtility::CalculateVectorFromAngle(angle);

			float speed = MyUtility::RandomFloat(60.0f, 300.0f);
			velocity.m_x *= speed;
			velocity.m_y *= speed;

			m_pBloodParticles[i].SetVelocity(velocity);
			++particles;
		}
	}
}

void ParticleEmitter::SpawnMuzzleFlash(Vector2 position, int angle)
{
	int particleAmount = MyUtility::RandomInt(50, 100);
	int particles = 0;

	for (int i = 0; i < MUZZLE_SIZE && particles < particleAmount; ++i)
	{
		if (m_pMuzzleParticles[i].IsDead())
		{
			m_pMuzzleParticles[i].Revive(position);
			int spreadDifference = 15;
			int addedAngle = MyUtility::RandomInt(-(spreadDifference), spreadDifference);

			int newAngle = static_cast<int>(fmod(angle + addedAngle, 360));

			Vector2 velocity = MyUtility::CalculateVectorFromAngle(newAngle);

			float minSpeed = 50.0f;
			float maxSpeed = 1000.0f;
			float speed = MyUtility::RandomFloat(minSpeed, maxSpeed);
			// Modify speed so that particles in the center are faster than others
			float interp = 1.0f - ((abs(static_cast<float>(addedAngle)) / static_cast<float>(spreadDifference)));
			m_pMuzzleParticles[i].m_aliveTime *= interp;

			velocity.m_x *= speed;
			velocity.m_y *= speed;

			m_pMuzzleParticles[i].SetVelocity(velocity);
			++particles;
		}
	}
}

void ParticleEmitter::CreateBloodParticles(BackBuffer& backBuffer)
{
	m_pBloodSprites = new Sprite*[3];
	m_pBloodSprites[0] = backBuffer.CreateSprite("..\\bin\\assets\\blood_spec_1.png");
	m_pBloodSprites[1] = backBuffer.CreateSprite("..\\bin\\assets\\blood_spec_2.png");
	m_pBloodSprites[2] = backBuffer.CreateSprite("..\\bin\\assets\\blood_spec_3.png");

	m_pBloodParticles = new Particle[BLOOD_SIZE];

	for (int i = 0; i < BLOOD_SIZE; ++i)
	{
		//m_pBloodParticles[i] = new Particle();
		int spriteIndex = MyUtility::RandomInt(0, 2);
		//LogManager::GetInstance().Log(std::to_string(spriteIndex).c_str());
		m_pBloodParticles[i].Initialise(m_pBloodSprites[spriteIndex], BLOOD_MIN_ALIVE_TIME, BLOOD_MAX_ALIVE_TIME);
	}
}

void ParticleEmitter::CreateMuzzleParticles(BackBuffer & backbuffer)
{
	m_pMuzzleSprite = backbuffer.CreateSprite("..\\bin\\assets\\muzzle_particle.png");

	m_pMuzzleParticles = new Particle[MUZZLE_SIZE];
	for (int i = 0; i < MUZZLE_SIZE; ++i)
	{
		m_pMuzzleParticles[i].Initialise(m_pMuzzleSprite, MUZZLE_MIN_ALIVE_TIME, MUZZLE_MAX_ALIVE_TIME);
	}
}
