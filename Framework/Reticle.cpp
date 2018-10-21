#include "Reticle.h"

#include "backbuffer.h"
#include "sprite.h"

#include <cassert>


Reticle::Reticle()
{
}


Reticle::~Reticle()
{
	delete m_pSprite;
	m_pSprite = 0;
}

void Reticle::Initialise(Sprite * sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	m_height = m_pSprite->GetHeight();
	m_width = m_pSprite->GetWidth();
}

void Reticle::SetPosition(Vector2 position)
{
	m_position = position;
}

void Reticle::SetVelocity(Vector2 velocity)
{
	m_velocity = velocity;
}

void Reticle::SetXVelocity(float x)
{
	m_velocity.m_x = x;
}

void Reticle::SetYVelocity(float y)
{
	m_velocity.m_y = y;
}

void Reticle::Process(float deltaTime)
{
	m_position.m_x += m_velocity.m_x * deltaTime;
	m_position.m_y += m_velocity.m_y * deltaTime;
}

void Reticle::Draw(BackBuffer & backBuffer)
{

	int x = static_cast<int>(m_position.m_x - m_width / 2);
	int y =  static_cast<int>(m_position.m_y - m_height / 2);

	backBuffer.DrawSpriteRotation(*m_pSprite, 0, x, y);
}

Vector2 Reticle::GetPosition() const
{
	return m_position;
}
