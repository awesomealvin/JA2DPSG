#include "Hand.h"
#include "game.h"
#include "sprite.h"
#include "backbuffer.h"
#include "MyUtility.h"
#include "logmanager.h"
#include <string>

Hand::Hand()
{
}


Hand::~Hand()
{
}

void Hand::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	// Creating the actual hand
	b2CircleShape circleShape;
	circleShape.m_radius = m_pSprite->GetWidth() / 2 * PTM;

	// Create fixture definition
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = true;

	// Collision filters
	fixtureDef.filter.categoryBits = C_MELEE;
	//fixtureDef.filter.maskBits = C_ENEMIES;

	// Create the fixture
	m_body->CreateFixture(&fixtureDef);


}

void Hand::Draw(BackBuffer & backBuffer)
{
	

	b2Vec2 pos = m_body->GetPosition();
	b2CircleShape* shape = ((b2CircleShape*)m_body->GetFixtureList()->GetShape());
	float radius = shape->m_radius;

	//float width = v[1].x - v[0].x;
	//float height = v[2].y - v[0].y;

	float x1 = (pos.x - radius) * MTP;
	float y1 = (pos.y - radius) * MTP;

	backBuffer.DrawSpriteRotation(*m_pSprite, m_body->GetAngle(), static_cast<int>(x1), static_cast<int>(y1));

}

void Hand::SetPositionClamp(b2Vec2 playerPosition, Vector2 mousePosition, float maxRadius)
{
	// Convert all to world coords before sending into calcuation
	float mouseX = mousePosition.m_x * PTM;
	float mouseY = mousePosition.m_y * PTM;
	float radius = maxRadius * PTM;
	
	// Clamp the magnitude (length)
	// Also disregard of the player position... Still haven't figured out why, but it works :)
	b2Vec2 newPosition = MyUtility::GetInstance().ClampMagnitude(b2Vec2(mouseX - playerPosition.x, mouseY - playerPosition.y), radius);

	newPosition.x += playerPosition.x;
	newPosition.y += playerPosition.y;

	m_body->SetTransform(newPosition, m_body->GetAngle());

	// Set the direction of the hand
	m_direction = MyUtility::GetInstance().GetDirection(playerPosition, b2Vec2(mouseX, mouseY));
	m_direction.Normalize();
}

void Hand::SetPositionClamp(b2Vec2 position, b2Vec2 aimingPosition, float maxRadius)
{
	Vector2 convertedVector(aimingPosition.x * MTP, aimingPosition.y * MTP);
	SetPositionClamp(position, convertedVector, maxRadius);
}

void Hand::SetOffsetHandFixture(Vector2 offset)
{
	b2Fixture* fixture = m_body->GetFixtureList();
	b2CircleShape* shape = (static_cast<b2CircleShape*>(fixture->GetShape()));
	shape->m_p.x = offset.m_x * PTM;
	shape->m_p.y = offset.m_y * PTM;
}

b2Vec2 Hand::GetOffsetHandPosition() const
{
	b2Fixture* fixture = m_body->GetFixtureList();
	b2CircleShape* shape = (static_cast<b2CircleShape*>(fixture->GetShape()));

	return shape->m_p;
}

void Hand::SetOffsetWeaponFixture(Vector2 offset)
{

}

b2Vec2 Hand::GetOffsetWeaponPosition() const
{
	return b2Vec2();
}

b2Vec2 Hand::GetDirection() const
{
	return m_direction;
}
