#include "Particle.h"

#include "MyUtility.h"
#include "sprite.h"
#include "backbuffer.h"

Particle::Particle()
{
}


Particle::~Particle()
{
}

bool Particle::Initialise(Sprite * sprite, float minAliveTime, float maxAliveTime)
{
	Entity::Initialise(sprite);
	m_minAliveTime = minAliveTime;
	m_maxAliveTime = maxAliveTime;
	m_currentTime = 0;
	m_currentAliveTime = 0;

	return true;
}

void Particle::Revive(Vector2 position)
{
	m_dead = false;
	m_currentAliveTime = 0;

	m_aliveTime = MyUtility::RandomFloat(m_minAliveTime, m_maxAliveTime);

	m_position.m_x = position.m_x - (m_pSprite->GetWidth() / 2);
	m_position.m_y = position.m_y - (m_pSprite->GetHeight() / 2);
}

void Particle::Process(float deltaTime)
{
	m_position.m_x += m_velocity.m_x * deltaTime;
	m_position.m_y += m_velocity.m_y * deltaTime;

	m_currentAliveTime += deltaTime;
	if (m_currentAliveTime >= m_aliveTime)
	{
		m_dead = true;
	}
}

void Particle::Draw(BackBuffer & backBuffer)
{
	backBuffer.DrawSpriteRotation(*m_pSprite, 0, static_cast<int>(m_position.m_x), static_cast<int>(m_position.m_y));
}
