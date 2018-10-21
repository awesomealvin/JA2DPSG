#include "Ball.h"
#include "backbuffer.h"
#include "logmanager.h"

#include <string>

// TODO: MAKE AN OBJECTS CLASS FOR ENVIRONMENTAL OBJECTS

Ball::Ball()
{

}


Ball::~Ball()
{
}

void Ball::Set(float radius)
{
	m_radius = radius;
}

void Ball::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = m_radius * PTM;


	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.2f;

	// Collision filters
	fixtureDef.filter.categoryBits = C_OBJECTS;
	fixtureDef.filter.maskBits = C_GROUND | C_PLAYER | C_WEAPONS | C_BULLETS | C_OBJECTS | C_ENEMIES;


	// Create the fixture
	m_body->CreateFixture(&fixtureDef);
}

void Ball::Draw(BackBuffer & backBuffer)
{


	b2Vec2 pos = m_body->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float radius = shape->m_radius * MTP;
	
	float x1 = (pos.x) * MTP;
	float y1 = (pos.y) * MTP;

	float angle = m_body->GetAngle();

	//std::string debug = std::to_string(angle);
	//LogManager::GetInstance().Log(debug.c_str());

	backBuffer.DrawCircle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(radius), angle);
}

EntityTypes Ball::GetType() const
{
	return EntityTypes::BALL;
}
