#include "EnemyDeathParticle.h"

#include "game.h"
#include "sprite.h"
#include "backbuffer.h"
#include "DebugUI.h"

EnemyDeathParticle::EnemyDeathParticle()
{
	
}


EnemyDeathParticle::~EnemyDeathParticle()
{

}


void EnemyDeathParticle::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;

	float width = static_cast<float>(m_pSprite->GetWidth());
	float height = static_cast<float>(m_pSprite->GetHeight());

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(width * PTM / 2, height * PTM / 2);

	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;


	// Collision filters
	fixtureDef.filter.categoryBits = C_OBJECTS;
	fixtureDef.filter.maskBits = C_GROUND | C_OBJECTS;

	m_body->CreateFixture(&fixtureDef);


}

void EnemyDeathParticle::Process(float deltaTime)
{
	Entity::Process(deltaTime);
	
	ProcessDecay(deltaTime);
}

void EnemyDeathParticle::Draw(BackBuffer & backBuffer)
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

EntityTypes EnemyDeathParticle::GetType() const
{
	return EntityTypes::OBJECTS;
}
