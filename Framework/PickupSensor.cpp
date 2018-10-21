#include "PickupSensor.h"
#include "game.h"
#include "backbuffer.h"
#include "player.h"
#include "logmanager.h"
#include "SoundManager.h"
#include "DebugUI.h"

PickupSensor::PickupSensor()
	: m_thrownWeaponTime(0.5f)
	, m_t(0.0f)
	, m_timeStart(false)
{
	m_name = "Pickup Sensor";
	m_toPickupWeapon = false;
	m_pickingUpWeapon = false;
}


PickupSensor::~PickupSensor()
{
}

void PickupSensor::Activate(float x, float y, Weapon* thrownWeapon)
{
	Activate(b2Vec2(x*PTM, y*PTM), thrownWeapon);
}

void PickupSensor::InitialiseBody(b2World * world)
{
	m_radius = 30.0f;

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(0.0f, 0.0f);
	m_body = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = m_radius * PTM;

	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.isSensor = true;

	// Collision filters
	fixtureDef.filter.categoryBits = C_PICKUP_SENSOR;
	fixtureDef.filter.maskBits = C_WEAPONS;
	m_body->SetUserData(this);


	// Create the fixture
	m_body->CreateFixture(&fixtureDef);
	//m_body->SetActive(false);
}

void PickupSensor::SetPlayer(Player * player)
{
	m_player = player;
}

void PickupSensor::Draw(BackBuffer & backBuffer)
{
	if (DebugUI::GetInstance().m_drawHitBoxes)
	{
		b2Vec2 pos = m_body->GetPosition();
		b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape());
		b2Vec2* v = shape->m_vertices;

		float radius = shape->m_radius * MTP;

		float x1 = (pos.x) * MTP;
		float y1 = (pos.y) * MTP;

		float angle = m_body->GetAngle() * MTP;

		//std::string debug = std::to_string(angle);
		//LogManager::GetInstance().Log(debug.c_str());

		backBuffer.DrawCircle(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(radius), angle);
	}

	
}

void PickupSensor::Activate(b2Vec2 position, Weapon* thrownWeapon)
{
	m_thrownWeapon = thrownWeapon;

	SetDead(false);
	m_body->SetTransform(position, m_body->GetAngle());

	m_toPickupWeapon = true;
	m_weaponToPickup = 0;
		
	m_timeStart = true;
	m_t = 0.0f;
}

void PickupSensor::Process(float deltaTime)
{
	Entity::Process(deltaTime);


	if (m_pickingUpWeapon)
	{

		if (m_weaponToPickup != 0)
		{
			m_player->SetWeapon(m_weaponToPickup);
		}

		m_pickingUpWeapon = false;
		m_toPickupWeapon = false;
		SetDead(true);
	}


	if (m_toPickupWeapon)
	{
		m_pickingUpWeapon = true;
	}

	if (m_timeStart)
	{
		m_t += deltaTime;
		if (m_t >= m_thrownWeaponTime)
		{
			m_thrownWeapon = 0;
			m_timeStart = false;
		}
	}


}

EntityTypes PickupSensor::GetType() const
{
	return EntityTypes::PICKUP_SENSOR;
}

void PickupSensor::OnCollisionBegin(Entity * other, b2Contact * contact)
{
	//std::string debug = GetName() + " Contact With: " + other->GetName();
	//LogManager::GetInstance().Log(debug.c_str());

	if (other->GetType() == EntityTypes::WEAPONS)
	{
		Weapon* weapon = static_cast<Weapon*>(other);
		if (m_thrownWeapon != weapon)
		{
			LogManager::GetInstance().Log("PickupSensor: Pickuped");
			m_weaponToPickup = weapon;
			SoundManager::GetInstance().PlaySoundPistolHandling();
		}	
	}
}



