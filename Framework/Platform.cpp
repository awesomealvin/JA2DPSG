#include "Platform.h"
#include "sprite.h"

#include <string>

Platform::Platform()
{
}

Platform::Platform(int width, int height)
{
}


Platform::~Platform()
{

}

void Platform::Set(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Platform::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;
	m_width = m_pSprite->GetWidth();
	m_height = m_pSprite->GetHeight();

	// Create ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_kinematicBody;
	groundBodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&groundBodyDef);
	

	// Create the shape for the ground
	b2PolygonShape groundBox;
	groundBox.SetAsBox(m_width * PTM/2, m_height *PTM/2);
	m_body->CreateFixture(&groundBox, 0.0f);

	// Make it static
	b2Filter filter = m_body->GetFixtureList()->GetFilterData();
	filter.categoryBits = C_GROUND;
	filter.maskBits = C_PLAYER | C_WEAPONS | C_BULLETS | C_OBJECTS | C_ENEMIES | C_HITBOX;
	m_body->SetUserData(this);

	m_body->GetFixtureList()->SetFilterData(filter);

}

void Platform::Draw(BackBuffer & backBuffer)
{

	b2Vec2 pos = m_body->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;

	/*std::string debug = std::to_string(pos.x);
	debug += ", ";
	debug += std::to_string(pos.y);

	LogManager::GetInstance().Log(debug.c_str());*/
	float width = v[1].x - v[0].x;
	float height = v[2].y - v[0].y;

	float x1 = (pos.x + v[0].x) * MTP;
	float y1 = (pos.y + v[0].y) * MTP;

	float x2 = width * MTP;
	float y2 = height * MTP;
	
	//backBuffer.DrawRectangle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
	backBuffer.DrawSpriteRotation(*m_pSprite, m_body->GetAngle(), static_cast<int>(x1), static_cast<int>(y1));

	/*std::string debug = std::to_string(v[0].y);
	LogManager::GetInstance().Log(debug.c_str());*/
}

EntityTypes Platform::GetType() const
{
	EntityTypes returnType = EntityTypes::PLATFORM;
	
	Vector2 pos = GetPixelPosition();

	if (pos.m_y < m_height) // Checks ceiling 
	{
		returnType = EntityTypes::GROUND;
	}
	else if (pos.m_x < m_width && m_height > m_width) // Checks left wall
	{
		returnType = EntityTypes::GROUND;
	}
	else if (pos.m_y > 720 - m_height && m_width > m_height) // Checks botton floor
	{
		returnType = EntityTypes::GROUND;
	}
	else if (pos.m_x > 1280 - m_width && m_height > m_width)
	{
		returnType = EntityTypes::GROUND;

	}
	else if (m_width > m_height)
	{
		returnType = EntityTypes::PLATFORM;
	}
	else if (m_height > m_width)
	{
		returnType = EntityTypes::WALL;
	}

	
	return returnType;
}
