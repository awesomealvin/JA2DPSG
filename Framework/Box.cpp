#include "Box.h"

#include "game.h"

Box::Box()
{
	m_width = 0;
	m_height = 0;
}


Box::Box(float width, float height)
{
	m_width = width;
	m_height = height;
}

Box::~Box()
{

}

void Box::InitialiseBody(b2World* world, Vector2 position)
{
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

	fixtureDef.filter.categoryBits = C_OBJECTS;
	fixtureDef.filter.maskBits = C_GROUND | C_PLAYER | C_WEAPONS | C_BULLETS | C_OBJECTS | C_ENEMIES;

	// Create the fixture
	m_body->CreateFixture(&fixtureDef);
}

void Box::Draw(BackBuffer & backBuffer)
{
	b2Vec2 pos = m_body->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;
	
	float width = v[1].x - v[0].x;
	float height = v[2].y - v[0].y;

	float x1 = (pos.x + v[0].x) * MTP;
	float y1 = (pos.y + v[0].y) * MTP;

	float x2 = width * MTP;
	float y2 = height * MTP;

	backBuffer.DrawRectangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
	//backBuffer.DrawRectangle2(x1, y1, x2, y2);
}
