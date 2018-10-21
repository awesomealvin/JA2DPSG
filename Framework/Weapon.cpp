#include "Weapon.h"
#include "game.h"
#include "backbuffer.h"
#include "sprite.h"
#include "logmanager.h"
#include "Bullet.h"
#include "EnemyDeathParticle.h"
#include "EnemyDeathParticleSystem.h"
#include "SoundManager.h"
#include "ParticleEmitter.h"
#include "MyUtility.h"
#include "DebugUI.h"

#include "entity.h"
#include <string>


Weapon::Weapon()
	: m_isOwned(false)
	, m_playerOwned(false)
	, m_owner(0)
{
	m_flip = false;
}


Weapon::~Weapon()
{
}

void Weapon::InitialiseBody(b2World * world, Vector2 position)
{
	m_width = m_pSprite->GetWidth();
	m_height = m_pSprite->GetHeight();

	m_position = position;

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	// Create polygon shape from the dynamic body
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_width * PTM / 2, m_height  * PTM / 2);

	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	fixtureDef.filter.categoryBits = C_WEAPONS;
	fixtureDef.filter.maskBits = C_GROUND | C_WEAPONS | C_BULLETS | C_OBJECTS | C_ENEMIES | C_PICKUP_SENSOR;
	m_body->SetUserData(this);
	m_body->SetSleepingAllowed(false); // so the sensor can detect

	// Create the fixture
	m_body->CreateFixture(&fixtureDef);


	// FIXTURE FOR SHOOTING POINT
	b2CircleShape circleShape;
	circleShape.m_radius = 0.1f;
	circleShape.m_p.Set(m_shootingPoint.m_x * PTM, -m_shootingPoint.m_y * PTM);

	b2FixtureDef fixtureWeapon;
	fixtureWeapon.shape = &circleShape;
	fixtureWeapon.isSensor = true;
	m_body->CreateFixture(&fixtureWeapon);

	// FIXTURE FOR SHOOTING POINT (FLIPPED)
	b2CircleShape circleShape2;
	circleShape2.m_radius = 0.1f;
	circleShape2.m_p.Set(m_shootingPoint.m_x * PTM, m_shootingPoint.m_y * PTM);

	b2FixtureDef fixtureWeapon2;
	fixtureWeapon2.shape = &circleShape2;
	fixtureWeapon2.isSensor = true;
	m_body->CreateFixture(&fixtureWeapon2);
}

void Weapon::Draw(BackBuffer & backBuffer)
{
	// For now, just draw a rectangle

	b2Vec2 pos = m_body->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetNext()->GetNext()->GetShape());
	b2Vec2* v = shape->m_vertices;

	//float width = v[1].x - v[0].x;
	//float height = v[2].y - v[0].y;

	float x1 = (pos.x + v[0].x) * MTP;
	float y1 = (pos.y + v[0].y) * MTP;

	/*float x2 = width * MTP;
	float y2 = height * MTP;*/

	//backBuffer.DrawSpriteRotation(*m_pSprite, m_body->GetAngle(), x1, y1);
	backBuffer.DrawSpriteRotation(*m_pSprite, m_body->GetAngle(), static_cast<int>(x1), static_cast<int>(y1), m_flip);

	//b2PolygonShape* shape2 = ((b2PolygonShape*)m_body->GetWorldPoint().
	//b2Vec2* v2 = 
	if (DebugUI::GetInstance().m_drawHitBoxes)
	{
		backBuffer.DrawHitBox(v, static_cast<int>(pos.x * MTP), static_cast<int>(pos.y * MTP), m_body->GetAngle());
	}
}

void Weapon::Process(float deltaTime)
{
	Entity::Process(deltaTime);
}

void Weapon::OnPickup()
{
	FilterIgnorePlayer();

}

void Weapon::FilterIgnorePlayer()
{
	// Set Filtering to ignore player
	b2Filter filter = m_body->GetFixtureList()->GetFilterData();
	filter.maskBits = C_GROUND | C_WEAPONS | C_BULLETS | C_OBJECTS | C_ENEMIES;

	m_body->GetFixtureList()->SetFilterData(filter);
}

void Weapon::FilterAddPlayer()
{
	// Set Filtering to ignore player
	b2Filter filter = m_body->GetFixtureList()->GetFilterData();
	filter.maskBits = C_GROUND | C_WEAPONS | C_BULLETS | C_OBJECTS | C_ENEMIES | C_PLAYER;

	m_body->GetFixtureList()->SetFilterData(filter);
}

void Weapon::SetFlip(bool flip)
{
	m_flip = flip;
}


EntityTypes Weapon::GetType() const
{
	return EntityTypes::WEAPONS;
}

Vector2 Weapon::GetWeaponOffset() const
{
	return m_weaponOffset;
}

Vector2 Weapon::GetHandOffset() const
{
	return m_handOffset;
}

b2Vec2 Weapon::GetShootingPoint() const
{
	b2CircleShape* shape;
	if (m_flip)
	{
		shape = static_cast<b2CircleShape*>(m_body->GetFixtureList()->GetShape());

	}
	else
	{
		shape = static_cast<b2CircleShape*>(m_body->GetFixtureList()->GetNext()->GetShape());

	}
	return m_body->GetWorldPoint(shape->m_p);
}

void Weapon::Shoot(float angle, b2Vec2 direction)
{
	b2Vec2 shootingPosition = GetShootingPoint();
	Bullet * bullet = ObjectPool::GetInstance().GetBullet();
	bullet->SetOwner(m_playerOwned, this);
	bullet->Activate(shootingPosition);
	bullet->Reset();
	 
	// SHOOT!
	bullet->SetAngle(angle);

	direction.x *= 30;
	direction.y *= 30;

	bullet->AddForce(direction);

	Vector2 muzzlePos;
	muzzlePos.m_x = shootingPosition.x * MTP;
	muzzlePos.m_y = shootingPosition.y * MTP;
	ParticleEmitter::GetInstance().SpawnMuzzleFlash(muzzlePos, static_cast<int>(MyUtility::ToAngle((angle))));

	SoundManager::GetInstance().PlaySoundPistolShoot();
	
}

void Weapon::SetPlayerOwned(bool playerOwned)
{
	m_playerOwned = playerOwned;
}

bool Weapon::IsPlayerOwned() const
{
	return m_playerOwned;
}

void Weapon::SetOwned(bool owned)
{
	m_isOwned = owned;
}

bool Weapon::IsOwned() const
{
	return m_isOwned;
}

bool Weapon::IsFlipped() const
{
	return m_flip;
}

void Weapon::SetupShootingDelay()
{
	m_enemyShootingDelay = MyUtility::RandomFloat(m_minEnemyShootingDelay, m_maxEnemyShootingDelay);
	m_currentEnemyShootingTime = 0.0f;
}

void Weapon::ProcessShootingDelay(float deltaTime)
{
	m_currentEnemyShootingTime += deltaTime;
}

bool Weapon::EnemyCanShoot() const
{
	bool returnValue = false;
	if (m_currentEnemyShootingTime >= m_enemyShootingDelay)
	{
		returnValue = true;
	}
	return returnValue;
}

Character * Weapon::GetOwner()
{
	return m_owner;
}

void Weapon::SetOwner(Character * owner)
{
	m_owner = owner;
}

