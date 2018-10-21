#include "Character.h"

#include "logmanager.h"
#include "game.h"
#include "backbuffer.h"
#include "MyUtility.h"
#include "sprite.h"
#include "BloodExplosion.h"
#include "DebugUI.h"

#include <string>

Character::Character()
	: m_jumpState(GROUNDED)
	, m_jumpForce(7.0f)
	, m_handYOffset(-30.0f)
{
}

void Character::Draw(BackBuffer & backBuffer)
{
	bool drawDebugBoxes = DebugUI::GetInstance().m_drawHitBoxes;
	// FOR CIRCLE LEGS
	b2CircleShape* cShape = ((b2CircleShape*)m_movementFixture->GetShape());
	b2Vec2 pos = m_body->GetWorldPoint(cShape->m_p);

	b2Vec2 positionDebug = m_body->GetWorldPoint(cShape->m_p);
	backBuffer.DrawCircle(static_cast<int>(positionDebug.x * MTP), static_cast<int>(positionDebug.y * MTP), static_cast<int>(cShape->m_radius * MTP), 0);

	if (!m_hasWeapon)
	{
		m_hand.Draw(backBuffer);
	}

	//--- DRAW SPRITE ---//
	b2PolygonShape* pShape = (b2PolygonShape*)m_hitBoxFixture->GetShape();
	b2Vec2 boxPos = m_body->GetWorldPoint(pShape->m_centroid);
	b2Vec2* v = pShape->m_vertices;
	// Get position
	float x1 = (pos.x + v[0].x) * MTP;
	float y1 = ((pos.y + v[0].y)) * MTP;
	// Calculate the center of rotation
	Vector2 center;
	float radius = cShape->m_radius;
	b2Vec2 circleCenter = cShape->m_p;
	center.m_x = ((m_width / 2) - (pShape->m_centroid.x * MTP));
	center.m_y = ((m_height / 2) - (pShape->m_centroid.y * MTP));
	// Draw!
	backBuffer.DrawSpriteRotation(*m_pSprite, m_body->GetAngle(), static_cast<int>(x1), static_cast<int>(y1), center, false);

	if (drawDebugBoxes)
	{
		//--- DRAW HITBOX --//
		b2Vec2 bodyPos = m_body->GetPosition();
		backBuffer.DrawHitBox(v, static_cast<int>(bodyPos.x * MTP), static_cast<int>(bodyPos.y * MTP), m_body->GetAngle());
		// Draw center
		backBuffer.DrawCircle(static_cast<int>(bodyPos.x * MTP), static_cast<int>(bodyPos.y * MTP), 5, 0);
	}
	

}
void Character::Process(float deltaTime)
{
	Entity::Process(deltaTime);
	ApplyMovementForce(deltaTime);

	b2Vec2 position = m_body->GetPosition();
	position.y += m_handYOffset * PTM;
	m_aimingAngle = MyUtility::GetRadiansFromVectors(position, m_hand.GetWorldPosition());

	SetWeaponPosition();

	// Basic check if its on ground
	if (m_body->GetLinearVelocity().y == 0)
	{
		m_jumpState = GROUNDED;
	}
}

bool Character::Initialise(Sprite * sprite)
{
	Entity::Initialise(sprite);

	// Initialise the hand
	Sprite* handSprite = Game::GetInstance().GetBackBuffer()->CreateSprite("..\\bin\\assets\\hand.png");
	m_hand.Initialise(handSprite);

	m_lastBulletContactWorldPosition.x = 0.0f;
	m_lastBulletContactWorldPosition.y = 0.0f;
	m_lastBulletContactVelocity = 0.0f;

	return true;
}

void Character::InitialiseBody(b2World * world, Vector2 position)
{
	m_position = position;

	// Will need to have other values when separating the sprite from it's own hitbox(es).
	m_width = m_pSprite->GetWidth();
	m_height = m_pSprite->GetHeight();

	// Creating a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(m_position.GetX() * PTM, m_position.GetY() * PTM);
	m_body = world->CreateBody(&bodyDef);

	// Circle Shape for Movement
	b2CircleShape circleShape;
	circleShape.m_radius = m_width / 2 * PTM;
	m_movementCircleRadius = circleShape.m_radius;
	//circleShape.m_p.y = -circleShape.m_radius;

	// Create fixture definition using box
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 5.0f;

	// Collision filters
	fixtureDef.filter.categoryBits = m_categoryBits;
	fixtureDef.filter.maskBits = m_maskBits;

	// Create the fixture
	m_movementFixture = m_body->CreateFixture(&fixtureDef);

	// Create polygon shape from the dynamic body
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(m_width * PTM / 2, m_height  * PTM / 2);

	// Polygon Shape for the hitbox
	b2PolygonShape boxShape;
	boxShape.SetAsBox((m_width)* PTM / 2, (m_height)* PTM / 2, b2Vec2(0, -circleShape.m_radius - (1 * PTM)), 0.0f);

	// Fixture
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.isSensor = true;

	// Collision Filters
	boxFixtureDef.filter.categoryBits = C_HITBOX;
	boxFixtureDef.filter.maskBits = C_BULLETS | C_GROUND;
	m_hitBoxFixture = m_body->CreateFixture(&boxFixtureDef);

	// Initialise Pickup Sensor
	m_hand.InitialiseBody(world, position);

	m_body->SetUserData(this);

}

void Character::ApplyMovementForce(float deltaTime)
{
	if (m_movementState != STATIONARY)
	{
		float force = 0;
		if (m_movementState == MOVERIGHT)
		{
			force = m_maxMovementForce;
		}
		else if (m_movementState == MOVELEFT)
		{
			force = -m_maxMovementForce;
		}

		b2Vec2 vel = m_body->GetLinearVelocity();
		float velChange = force - vel.x;
		float appliedForce = m_body->GetMass() * velChange;

		m_body->ApplyLinearImpulse(b2Vec2(appliedForce, 0), m_body->GetLocalCenter(), true);
	}
}

void Character::MoveLeft()
{

	m_movementState = MOVELEFT;

}

void Character::MoveRight()
{
	m_movementState = MOVERIGHT;

}

void Character::Jump()
{
	
	if (m_jumpState == GROUNDED || m_jumpState == JUMPED)
	{
		ResetVelocities();
		float appliedForce = m_jumpForce * m_body->GetMass();
		m_body->ApplyLinearImpulse(b2Vec2(0.0f, -appliedForce), m_body->GetWorldCenter(), true);

		if (m_jumpState == GROUNDED)
		{
			m_jumpState = JUMPED;
		} 
		else if (m_jumpState == JUMPED)
		{
			m_jumpState = DOUBLE_JUMPED;
		}	
	}
	
}

void Character::Stop()
{
	m_movementState = STATIONARY;

}

void Character::SetBodyCanRotate(bool canRotate)
{
	m_body->SetFixedRotation(!canRotate);
	m_hitBoxFixture->SetSensor(false);
}

void Character::Shoot()
{
	if (m_hasWeapon) {
		m_equippedWeapon->Shoot(m_aimingAngle, m_hand.GetDirection());
	}
}

void Character::SetWeapon(Weapon * weapon)
{
	LogManager::GetInstance().Log("Character.cpp - SetWeapon(): Setting Weapon...");

	if (weapon->GetOwner())
	{
		weapon->GetOwner()->DropWeapon();
	}
	m_equippedWeapon = weapon;
	m_equippedWeapon->SetOwned(true);
	m_equippedWeapon->SetOwner(this);
	m_hasWeapon = true;

	// STEAL WEAPON FROM PLAYER


}

bool Character::HasWeapon() const
{
	return m_hasWeapon;
}

void Character::Reset()
{
	m_equippedWeapon = 0;
	m_hasWeapon = false;
}

void Character::DropWeapon()
{
	if (m_hasWeapon || m_equippedWeapon != 0)
	{
		m_equippedWeapon->SetOwned(false);
		m_equippedWeapon->SetOwner(0);
		m_equippedWeapon = 0;
		m_hasWeapon = false;
	}
}

void Character::SpawnBloodExplosion(int minAmount, int maxAmount)
{
	b2Vec2 worldPosition = GetWorldPosition();
	worldPosition.y -= m_movementCircleRadius;

	Vector2 spawnPosition;
	spawnPosition.m_x = worldPosition.x * MTP;
	spawnPosition.m_y = worldPosition.y * MTP;
	ParticleEmitter::GetInstance().SpawnBloodExplosion(spawnPosition, minAmount, maxAmount);


	BloodExplosion* be = ObjectPool::GetInstance().GetBloodExplosion();
	if (be != 0)
	{
		spawnPosition.m_y -= be->GetFrameHeight() / 2;
		spawnPosition.m_x -= be->GetFrameWidth() / 2;
		be->SetPixelPosition(spawnPosition);
		be->StartAnimating();
	}
	



}

void Character::OnCollisionPreSolve(Entity * other, b2Contact * contact, const b2Manifold * oldManifold)
{
	if (other->GetType() == EntityTypes::PLATFORM)
	{
		float yVelocity = m_body->GetLinearVelocityFromWorldPoint(m_body->GetPosition()).y;
		if (yVelocity < 0.0f)
		{
			contact->SetEnabled(false);
		}
	}
}


void Character::SetWeaponPosition()
{
	if (m_hasWeapon)
	{
		MyUtility util = MyUtility::GetInstance();

		m_equippedWeapon->SetPosition(m_hand.GetWorldPosition());
		m_equippedWeapon->SetAngle(m_aimingAngle);


		// Check if the sprite should flip
		float angleDegrees = util.ToAngle(m_aimingAngle);
		if ((angleDegrees >= 90.0f && angleDegrees <= 180.0f) || (angleDegrees >= -180.0f && angleDegrees <= -90.0f))
		{
			m_equippedWeapon->SetFlip(true);
		}
		else
		{
			m_equippedWeapon->SetFlip(false);
		}
	}
}
