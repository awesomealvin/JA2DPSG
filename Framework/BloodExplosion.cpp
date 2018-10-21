#include "BloodExplosion.h"

#include "animatedsprite.h"
#include "MyUtility.h"

BloodExplosion::BloodExplosion()
{
}


BloodExplosion::~BloodExplosion()
{
	delete m_pAnimatedSprite;
	m_pAnimatedSprite = 0;
}

void BloodExplosion::Process(float deltaTime)
{
	Entity::Process(deltaTime);
	m_pAnimatedSprite->Process(deltaTime);
	if (!m_pAnimatedSprite->IsAnimating())
	{
		//LogManager::GetInstance().Log("SET DEAD");
		m_dead = true;
	}
}

void BloodExplosion::Draw(BackBuffer & backBuffer)
{
	assert(m_pAnimatedSprite);
	m_pAnimatedSprite->SetX(static_cast<int>(m_position.m_x));
	m_pAnimatedSprite->SetY(static_cast<int>(m_position.m_y));
	m_pAnimatedSprite->Draw(backBuffer);
}

EntityTypes BloodExplosion::GetType() const
{
	return EntityTypes::OBJECTS;
}

void BloodExplosion::DestroySprite()
{
	// do nothing
}

void BloodExplosion::StartAnimating()
{
	Entity::StartAnimating();
	int rand = MyUtility::RandomInt(0, 3);
	m_pAnimatedSprite->SetYCoord(rand*m_numAnimations);
}
