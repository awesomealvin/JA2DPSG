// COMP710 GP 2D Framework 2018

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "game.h"
#include "logmanager.h"
#include "MyUtility.h"
#include "animatedsprite.h"

// Library includes:
#include <cassert>

Entity::Entity()
	: m_pSprite(0)
	, m_dead(false)
	, m_toSetDead(false)
	, m_settingDead(false)
	, m_toTransformBody(false)
	, m_transformingBody(false)
	, m_isDecaying(false)
	, DECAY_TIME(5.0f)
	, m_currentTime(0.0f)
	, m_alpha(255)
	, m_toAddForceValue(b2Vec2_zero)
	, m_toAddForce(false)
	, m_addingForce(false)
	, m_isAnimated(false)
	, m_spriteSheetYPosition(0)
	, m_frameWidth(0)
	, m_frameHeight(0)
	, m_numAnimations(0)
{

}

Entity::~Entity()
{
	//if (m_pSprite != 0)
	//{
	//	delete m_pSprite;
	//	m_pSprite = 0;
	//}
}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return (true);
}

bool Entity::Initialise(AnimatedSprite * animatedSprite, int frameHeight, int frameWidth)
{
	assert(animatedSprite);
	m_pAnimatedSprite = animatedSprite;

	m_isAnimated = true;
	m_spriteSheetYPosition = 0;
	m_frameHeight = frameHeight;
	m_frameWidth = frameWidth;
	m_pAnimatedSprite->SetFrameHeight(m_frameHeight);
	m_pAnimatedSprite->SetFrameWidth(m_frameWidth);

	int sheetWidth = m_pAnimatedSprite->GetWidth();
	int sheetHeight = m_pAnimatedSprite->GetHeight();
	int numFrames = sheetWidth / m_frameWidth;
	m_numAnimations = sheetHeight / m_frameHeight;
	
	for (int i = 0; i < numFrames; ++i)
	{
		m_pAnimatedSprite->AddFrame(i * m_frameWidth);
	}

	m_pAnimatedSprite->SetFrameSpeed(0.075f);

	return (true);
	
}


std::string Entity::GetName() const
{
	return m_name;
}

void
Entity::Process(float deltaTime)
{
	
	if (m_settingDead)
	{
		SetDead(m_toSetDeadValue);
		m_toSetDead = false;
		m_settingDead = false;
	}
	if (m_transformingBody)
	{
		SetPosition(m_toTransformValue);
		m_transformingBody = false;
		m_toTransformBody = false;
		//m_addingForce = true;
	}
	if (m_addingForce)
	{
		AddForce(m_toAddForceValue);
		m_toAddForce = false;
		m_addingForce = false;
	}

	
	if (m_toSetDead)
	{
		m_settingDead = true;
	}

	if (m_toTransformBody)
	{
		m_transformingBody = true;
	}

	if (m_toAddForce)
	{
		m_addingForce = true;
	}
}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_position.GetX()));
	m_pSprite->SetY(static_cast<int>(m_position.GetY()));
	m_pSprite->Draw(backBuffer);
}

void Entity::DestroySprite()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// W02.3: Generic Entity Collision routine.

	// W02.3: Does this object collide with the e object?
	// W02.3: Create a circle for each entity (this and e).

	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.

	// W02.3: Return result of collision.

	return (false); // W02.3 Change return value!
}

void
Entity::SetDead(bool dead)
{
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	m_body->SetAngularVelocity(0.0f);
	m_dead = dead;
	m_body->SetActive(!dead);
}

void Entity::SetDeadWithDelay(bool dead)
{
	m_toSetDeadValue = dead;
	m_toSetDead = true;
}

bool Entity::IsDead() const
{
	return m_dead;
}

bool Entity::ToSetDead() const
{
	return m_toSetDead;
}

bool Entity::ToTransformBody() const
{
	return m_toTransformBody;
}

bool Entity::IsDecaying() const
{
	return m_isDecaying;;
}

void Entity::Activate(Vector2 position)
{
	SetDead(false);
	SetPosition(position);
}

void Entity::Activate(b2Vec2 position)
{
	SetDead(false);
	SetPosition(position);
}

void Entity::SetPositionWithDelay(b2Vec2 position)
{
	m_toTransformBody = true;
	m_toTransformValue = position;
}

void
Entity::SetPosition(float x, float y)
{
	m_position.SetX(x);
	m_position.SetY(y);

	b2Vec2 pos;
	pos.x = x * PTM;
	pos.y = y * PTM;

	m_body->SetTransform(pos, m_body->GetAngle());
}

void Entity::SetPosition(b2Vec2 position)
{
	m_body->SetTransform(position, m_body->GetAngle());
}

void Entity::SetPosition(Vector2 position)
{
	b2Vec2 newPosition;
	newPosition.x = position.m_x * PTM;
	newPosition.y = position.m_y * PTM;

	m_body->SetTransform(newPosition, m_body->GetAngle());
}

void Entity::SetPixelPosition(Vector2 position)
{
	m_position = position;
}

void
Entity::SetPositionX(float x)
{
	m_position.SetX(x);
}

void
Entity::SetPositionY(float y)
{
	m_position.SetY(y);
}

void Entity::SetAngle(float angle)
{
	m_body->SetTransform(m_body->GetPosition(), angle);
}

void Entity::AddForce(b2Vec2 force)
{
	b2Vec2 appliedForce;
	appliedForce.x = force.x * m_body->GetMass();
	appliedForce.y = force.y * m_body->GetMass();

	m_body->ApplyLinearImpulse(appliedForce, m_body->GetWorldCenter(), true);
}

void Entity::AddForceWithDelay(b2Vec2 force)
{
	m_toAddForce = true;
	m_toAddForceValue = force;
}

void Entity::SetLinearVelocity(b2Vec2 vel)
{
	m_body->SetLinearVelocity(vel);
}

void Entity::SetAngularVelocity(float value)
{
	m_body->SetAngularVelocity(value);
}

void Entity::ApplyTorque(float amount)
{
	m_body->ApplyTorque(amount, true);
}

void Entity::ResetVelocities()
{
	m_body->SetLinearVelocity(b2Vec2_zero);
	m_body->SetAngularVelocity(0.0f);
}

float
Entity::GetPositionX() const
{
	return m_position.GetX();
}

float
Entity::GetPositionY() const
{
	return m_position.GetY();
}

Vector2 Entity::GetPixelPosition() const
{
	Vector2 pos;
	pos.m_x = (m_body->GetPosition().x * MTP);
	pos.m_y = (m_body->GetPosition().y * MTP);
	return pos;
}

Vector2 Entity::GetVelocity()
{
	return m_velocity;
}

void Entity::SetVelocity(Vector2 velocity)
{
	m_velocity = velocity;
}

b2Vec2 Entity::GetWorldPosition()
{
	return m_body->GetPosition();
}

int Entity::GetWidth() const
{
	return m_pSprite->GetWidth();
}

int Entity::GetHeight() const
{
	return m_pSprite->GetHeight();
}

void Entity::Reset()
{
}


EntityTypes Entity::GetType() const
{
	return EntityTypes::OBJECTS;
}

void Entity::StartContact()
{
	m_contacting = true;
}

void Entity::EndContact()
{
	m_contacting = false;
}

void Entity::OnCollisionBegin(Entity * other, b2Contact* contact)
{
}

void Entity::OnCollisionPostSolve(Entity * other, b2Contact * contact, const b2ContactImpulse * impulse)
{
}

void Entity::OnCollisionPreSolve(Entity* otherb2Contact, b2Contact * contact, const b2Manifold * oldManifold)
{

}

void Entity::StartAnimating()
{
	if (m_isAnimated)
	{
		m_pAnimatedSprite->StartAnimating();
	}
}

int Entity::GetFrameHeight() const
{
	return m_frameHeight;
}

int Entity::GetFrameWidth() const
{
	return m_frameWidth;
}

void Entity::ProcessDecay(float deltaTime)
{
	if (m_isDecaying)
	{
		m_alpha = static_cast<unsigned char>(MyUtility::GetInstance().Lerp(255, 0, m_currentTime));
		m_currentTime += (deltaTime / DECAY_TIME);
		if (m_currentTime >= 1.0f)
		{
			SetDead(true);
			m_isDecaying = false;
			m_alpha = 255;
		}
		//LogManager::GetInstance().Log(std::to_string(m_alpha).c_str());
	}
}

void Entity::StartDecay()
{
	if (!m_isDecaying)
	{
		m_isDecaying = true;
		m_currentTime = 0.0f;
	}
}





