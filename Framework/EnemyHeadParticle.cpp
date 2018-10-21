#include "EnemyHeadParticle.h"

#include "sprite.h"
#include "backbuffer.h"
#include "game.h"

EnemyHeadParticle::EnemyHeadParticle()
{
}


EnemyHeadParticle::~EnemyHeadParticle()
{
}

void EnemyHeadParticle::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;

	float radius = static_cast<float>(m_pSprite->GetWidth()/2);

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = radius * PTM;

	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.2f;

	// Collision filters
	fixtureDef.filter.categoryBits = C_OBJECTS;
	fixtureDef.filter.maskBits = C_GROUND | C_OBJECTS;

	// Create the fixture
	m_body->CreateFixture(&fixtureDef);
}

void EnemyHeadParticle::Process(float deltaTime)
{
	Entity::Process(deltaTime);

	ProcessDecay(deltaTime);
}

void EnemyHeadParticle::Draw(BackBuffer & backBuffer)
{
	b2CircleShape* shape = static_cast<b2CircleShape*>(m_body->GetFixtureList()->GetShape());

	b2Vec2 position = m_body->GetPosition();

	int radius = static_cast<int>(shape->m_radius * MTP);
	float angle = m_body->GetAngle();

	Vector2 pPos;
	pPos.Set((position.x * MTP), (position.y * MTP));
	pPos.m_x -= radius;
	pPos.m_y -= radius;

	backBuffer.DrawSpriteBall(*m_pSprite, angle, static_cast<int>(pPos.m_x), static_cast<int>(pPos.m_y), radius);

}

EntityTypes EnemyHeadParticle::GetType() const
{
	return EntityTypes::OBJECTS;
}
