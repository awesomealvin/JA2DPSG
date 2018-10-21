#include "Bullet.h"

#include "game.h"
#include "entity.h"
#include "sprite.h"
#include "backbuffer.h"
#include "logmanager.h"
#include "MyUtility.h"
#include "SoundManager.h"
#include "ParticleEmitter.h"
#include "Character.h"
#include "DebugUI.h"

Bullet::Bullet()
{

}


Bullet::~Bullet()
{

}

void Bullet::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;

	float width = static_cast<float>(m_pSprite->GetWidth());
	float height = static_cast<float>(m_pSprite->GetHeight());

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(width * PTM / 2, height * PTM / 2);


	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	//fixtureDef.isSensor = true;

	// Collision filters
	fixtureDef.filter.categoryBits = C_BULLETS;
	fixtureDef.filter.maskBits = C_GROUND | C_PLAYER | C_OBJECTS | C_BULLETS | C_HITBOX;
	m_body->SetUserData(this);


	// Create the fixture
	m_body->CreateFixture(&fixtureDef);
}

void Bullet::Draw(BackBuffer & backBuffer)
{
	b2Vec2 pos = m_body->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float x1 = (pos.x + v[0].x) * MTP;
	float y1 = (pos.y + v[0].y) * MTP;

	backBuffer.SetAlpha(*m_pSprite, m_alpha);
	//LogManager::GetInstance().Log(std::to_string(m_alpha).c_str());
	backBuffer.DrawSpriteRotation(*m_pSprite, m_body->GetAngle(), static_cast<int>(x1), static_cast<int>(y1));

	if (DebugUI::GetInstance().m_drawHitBoxes)
	{
		backBuffer.DrawHitBox(v, static_cast<int>(pos.x * MTP), static_cast<int>(pos.y * MTP), m_body->GetAngle());
	}

}

void Bullet::Process(float deltaTime)
{
	Entity::Process(deltaTime);

	if (!m_isDecaying)
	{
		b2Vec2 velocity = m_body->GetLinearVelocity();
		m_body->SetTransform(m_body->GetPosition(), atan2(velocity.y, velocity.x));
	}

	ProcessDecay(deltaTime);
}

EntityTypes Bullet::GetType() const
{
	return EntityTypes::BULLETS;
}

void Bullet::OnCollisionBegin(Entity * other, b2Contact* contact)
{

	if (other->GetType() == EntityTypes::GROUND)
	{
		if (!m_isDecaying)
		{
			SoundManager::GetInstance().PlaySoundImpact();
			StartDecay();
		}
	}
	else if (other->GetType() == EntityTypes::PLATFORM ||
		other->GetType() == EntityTypes::WALL)
	{
		if (contact->IsEnabled())
		{
			SoundManager::GetInstance().PlayCasingSound();
		}

	}
	else if (other->GetType() == EntityTypes::GROUND || other->GetType() == EntityTypes::BULLETS)
	{
		StartDecay();
	}
	else if (other->GetType() == EntityTypes::PLAYER)
	{

		if (m_owner != static_cast<Character*>(other))
		{
			StartDecay();
		}
	}


}

void Bullet::OnCollisionPreSolve(Entity * other, b2Contact * contact, const b2Manifold * oldManifold)
{
	if (other->GetType() == EntityTypes::PLATFORM ||
		other->GetType() == EntityTypes::WALL)
	{
		if (!m_isDecaying)
		{
			contact->SetEnabled(false);
		}
	}

}

void Bullet::Reset()
{
	m_isDecaying = false;
}

void Bullet::
SetOwner(bool playerOwned, Weapon * weaponOwner)
{
	m_playerOwned = playerOwned;
	m_weaponShotFrom = weaponOwner;
	m_owner = weaponOwner->GetOwner();
}

Character * Bullet::GetEntityOwner()
{
	return m_owner;
}

