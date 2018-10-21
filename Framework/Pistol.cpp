#include "Pistol.h"
#include "logmanager.h"

Pistol::Pistol()

{
	m_name = "Pistol";
	m_weaponOffset.Set(8, 3);
	m_shootingPoint.Set(8, 3);
	m_handOffset.Set(-5, -2);

	m_minEnemyShootingDelay = (1.0f);
	m_maxEnemyShootingDelay = (2.5f);
	m_currentEnemyShootingTime = (0.0f);
	m_enemyShootingDelay = (0.0f);
}


Pistol::~Pistol()
{
}

void Pistol::Process(float deltaTime)
{
	Gun::Process(deltaTime);
}
