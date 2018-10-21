#include "Player.h"
#include "game.h"
#include "backbuffer.h"
#include "MyUtility.h"
#include "Ball.h"
#include "sprite.h"
#include "SDL.h"
#include "logmanager.h"
#include "ObjectPool.h"
#include "bullet.h"
#include "SoundManager.h"
#include "DebugUI.h"

MyUtility util = MyUtility::GetInstance();

Player::Player()
{
	m_maxMovementForce = 2.0f;
	m_hasWeapon = false;
	m_pickupRange = 50.0f;
	m_categoryBits = C_PLAYER;
	m_maskBits = C_GROUND | C_BULLETS | C_OBJECTS;
}


Player::~Player()
{
	DestroySprite();
	m_hand.DestroySprite();
}

void Player::Draw(BackBuffer & backBuffer)
{
	// For now, just draw a rectangle

	// FOR BOX LEGS
	/*b2Vec2 pos = m_body->GetPosition();
	b2PolygonShape* shape = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape());
	b2Vec2* v = shape->m_vertices;

	float width = v[1].x - v[0].x;
	float height = v[2].y - v[0].y;

	float x1 = (pos.x + v[0].x) * MTP;
	float y1 = (pos.y + v[0].y) * MTP;*/

	Character::Draw(backBuffer);

	m_pickupSensor.Draw(backBuffer);
	m_reticle.Draw(backBuffer);

}

void Player::Process(float deltaTime)
{
	//float yVelocity = m_body->GetLinearVelocity().y;
	//DebugUI::GetInstance().SetLine(6, std::to_string(yVelocity));

	Character::Process(deltaTime);
	DebugUI::GetInstance().SetLine(2, "Jump State: " + std::to_string(m_jumpState));


	m_pickupSensor.Process(deltaTime);

	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	m_mousePosition.SetX(static_cast<float>(x));
	m_mousePosition.SetY(static_cast<float>(y));

	if ((m_mousePosition.m_x != m_previousMousePosition.m_x) &&
		(m_mousePosition.m_y != m_previousMousePosition.m_y))
	{
		m_reticle.SetPosition(m_mousePosition);
	}
	else
	{
		m_reticle.Process(deltaTime);
	}
	SetHandPosition();

	m_previousMousePosition = m_mousePosition;
}

bool Player::Initialise(Sprite * sprite, BackBuffer& backBuffer)
{
	Character::Initialise(sprite);
	m_pickupSensor.SetPlayer(this);

	Sprite* reticleSprite = backBuffer.CreateSprite("..\\bin\\assets\\reticle.png");
	m_reticle.Initialise(reticleSprite);

	return true;
}

void Player::InitialiseBody(b2World * world, Vector2 position)
{
	Character::InitialiseBody(world, position);

	// Initialise Pickup Sensor
	m_pickupSensor.InitialiseBody(world);

}


void Player::Pickup()
{

	Vector2 handPosition = m_hand.GetPixelPosition();
	m_pickupSensor.Activate(handPosition.m_x, handPosition.m_y, m_equippedWeapon);

	ThrowWeapon();

	m_equippedWeapon = 0;

	//// Check the distance between the mouse and player
	//Vector2 playerPosition = GetPixelPosition();
	//playerPosition.m_y += static_cast<int>(m_handYOffset);
	//Vector2 direction = MyUtility::GetDirection(playerPosition, m_mousePosition);
	//float length = MyUtility::GetMagnitude(direction);
	//LogManager::GetInstance().Log(("Magnitude: " + std::to_string(length)).c_str());

}

void Player::SetWeapon(Weapon * weapon)
{
	Character::SetWeapon(weapon);
	m_equippedWeapon->SetPlayerOwned(true);

	// Set Offsets for Hand
	//m_hand.SetOffsetHandFixture(weapon->GetHandOffset());
}

void Player::ThrowWeapon()
{
	// DROP WEAPON
	if (m_hasWeapon)
	{

		// Reset the velocity so that it is true to the calculations below
		m_equippedWeapon->SetLinearVelocity(b2Vec2_zero);
		m_equippedWeapon->SetAngularVelocity(0.0f);

		// Get the direction of the mouse/hand
		b2Vec2 dir = m_hand.GetDirection();

		// Apply Force
		dir.x *= 10.0f;
		dir.y *= 10.0f;
		m_equippedWeapon->AddForce(dir);

		// Add torque so that it spins
		float torqueForce = 0.75f;
		// Spins in in the direction thrown
		torqueForce = (m_equippedWeapon->IsFlipped()) ? -torqueForce : torqueForce;
		m_equippedWeapon->ApplyTorque(torqueForce);

		m_equippedWeapon->SetPlayerOwned(false);
		m_equippedWeapon->SetOwned(false);
		m_equippedWeapon->SetOwner(0);
		m_hasWeapon = false;
	}
}

void Player::SetReticleVelocity(Vector2 velocity)
{
	velocity.m_x *= 0.01f;
	velocity.m_y *= 0.01f;

	m_reticle.SetVelocity(velocity);
}

void Player::SetReticleXVelocity(int x)
{
	m_reticle.SetXVelocity(static_cast<float>(x) * 0.01f);
}

void Player::SetReticleYVelocity(int y)
{
	m_reticle.SetYVelocity(static_cast<float>(y) * 0.01f);
}

void Player::Die()
{
	SpawnBloodExplosion(100, 300);
	ResetVelocities();
	Game::GetInstance().StartGameOver(false);
}

EntityTypes Player::GetType() const
{
	return EntityTypes::PLAYER;
}

void Player::OnCollisionBegin(Entity * other, b2Contact * contact)
{
	if (other->GetType() == EntityTypes::BULLETS)
	{
		Bullet* b = static_cast<Bullet*>(other);
		if (b->GetEntityOwner() != this)
		{
			Die();
		}
	}
}

void Player::SetHandPosition()
{
	b2Vec2 playerPosition = m_body->GetPosition();
	playerPosition.y += m_handYOffset * PTM; // Offset for the shoulder position
	m_hand.SetPositionClamp(playerPosition, m_reticle.GetPosition(), 30.0f);

}


