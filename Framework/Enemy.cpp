#include "Enemy.h"

#include "EnemyDeadState.h"
#include "EnemyStillState.h"
#include "EnemyState.h"
#include "logmanager.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "ObjectPool.h"
#include "BloodExplosion.h"
#include "ParticleEmitter.h"
#include "game.h"
#include "DebugUI.h"

Enemy::Enemy()
	: m_minAimingRange(7.0f)
	, m_maxAimingRange(21.0f)
	, m_aimingRange(0.0f)
{
	m_movementState = STATIONARY;
	m_maxMovementForce = 2.0f;
	m_hasWeapon = false;
	m_pickupRange = 50.0f;
	m_categoryBits = C_ENEMIES;
	m_maskBits = C_GROUND | C_OBJECTS;
	m_currentState = &EnemyStillState::GetInstance();
	m_foundWeapon = 0;


	m_minAimingRange;
	m_maxAimingRange;
	m_aimingRange;
}


Enemy::~Enemy()
{
	Character::~Character();
	m_hand.DestroySprite();
}

void Enemy::Process(float deltaTime)
{
	Character::Process(deltaTime);
	m_currentState->Execute(*this, deltaTime);
	SetHandPosition();
}

EntityTypes Enemy::GetType() const
{
	return EntityTypes::ENEMIES;
}

void Enemy::OnCollisionBegin(Entity * other, b2Contact * contact)
{
	if (other->GetType() == EntityTypes::BULLETS)
	{
		Bullet * b = static_cast<Bullet*>(other);
		if (!b->IsDecaying())
		{
			b->StartDecay();
			/*b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);*/

			m_lastBulletContactWorldPosition = b->GetWorldPosition();/*worldManifold.points[0];*/
			LogManager::GetInstance().Log("Enemy.cpp: Enemy hit with bullet.");
			ChangeState(&EnemyDeadState::GetInstance());

			// Play sound
			SoundManager::GetInstance().PlaySoundGoreHit();
	
		}
	}
}

void Enemy::OnCollisionPostSolve(Entity * other, b2Contact * contact, const b2ContactImpulse * impulse)
{
	
}

void Enemy::ChangeState(EnemyState * state)
{
	m_currentState = state;
	m_currentState->Enter(*this);
}

bool Enemy::HasFoundPlayer() const
{
	return m_foundPlayer;
}

void Enemy::SetFoundPlayer(bool found)
{
	m_foundPlayer = found;
}

void Enemy::SetAimingLocation(b2Vec2 aimingLocation)
{
	m_aimingLocation = aimingLocation;
}

b2Vec2 Enemy::GetAimingLocation()
{
	return m_aimingLocation;
}

bool Enemy::CanShoot() const
{
	return (m_equippedWeapon->EnemyCanShoot());
}

void Enemy::AddCurrentShootingTime(float deltaTime)
{
	m_equippedWeapon->ProcessShootingDelay(deltaTime);
}

void Enemy::ResetCurrentShootingTime()
{
	m_equippedWeapon->SetupShootingDelay();
}


void Enemy::Reset()
{
	Character::Reset();
	DropWeapon();

	ChangeState(&EnemyStillState::GetInstance());
}

void Enemy::SetAimingRange()
{
	m_aimingRange = MyUtility::RandomFloat(m_minAimingRange, m_maxAimingRange);
}

float Enemy::GetAimingRange() const
{
	return m_aimingRange;
}

void Enemy::SetHandPosition()
{
	b2Vec2 position = m_body->GetPosition();
	position.y += m_handYOffset * PTM; // Offset for the shoulder position
	m_hand.SetPositionClamp(position, m_aimingLocation, 30.0f);
	
	//DebugUI::GetInstance().SetLine(1, std::to_string(m_hand.Po)
}


