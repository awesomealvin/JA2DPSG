// COMP710 GP 2D Framework 2018
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;
class AnimatedSprite;

#include "Vector2.h"
#include "Box2D/Box2D.h"
#include "EntityTypes.h"
#include <string>

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();

	bool Initialise(Sprite* sprite);
	bool Initialise(AnimatedSprite* animatedSprite, int frameHeight, int frameWidth);
	void InitialiseBody(b2World* world, Vector2 position);

	std::string GetName() const;

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void DestroySprite();

	void SetDead(bool dead);
	void SetDeadWithDelay(bool dead);
	bool IsDead() const;
	bool ToSetDead() const;
	bool ToTransformBody() const;

	void StartDecay();
	bool IsDecaying() const;

	void Activate(Vector2 position);
	void Activate(b2Vec2 position);
	void SetPositionWithDelay(b2Vec2 position);

	bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPosition(b2Vec2 position);
	void SetPosition(Vector2 position);
	void SetPixelPosition(Vector2 position);
	void SetPositionX(float x);
	void SetPositionY(float y);

	void SetAngle(float angle);
	void AddForce(b2Vec2 force);
	void AddForceWithDelay(b2Vec2 force);
	void SetLinearVelocity(b2Vec2 vel);
	void SetAngularVelocity(float value);
	void ApplyTorque(float amount);
	void ResetVelocities();

	float GetPositionX() const;
	float GetPositionY() const;

	Vector2 GetPixelPosition() const;
	Vector2 GetVelocity();
	void SetVelocity(Vector2 velocity);

	b2Vec2 GetWorldPosition();

	int GetWidth() const;
	int GetHeight() const;

	virtual void Reset();


	enum EntityCategory
	{
		C_GROUND = 1,
		C_PLAYER = 2,
		C_WEAPONS = 4,
		C_BULLETS = 8,
		C_OBJECTS = 16,
		C_ENEMIES = 32,
		C_PICKUP_SENSOR = 64,
		C_MELEE = 128,
		C_HITBOX = 256
	};

	virtual EntityTypes GetType() const;

	void StartContact();
	void EndContact();
	virtual void OnCollisionBegin(Entity* other, b2Contact* contact);
	virtual void OnCollisionPostSolve(Entity* other, b2Contact* contact, const b2ContactImpulse* impulse);
	virtual void OnCollisionPreSolve(Entity* other, b2Contact* contact, const b2Manifold* oldManifold);


	void StartAnimating();
	int GetFrameHeight() const;
	int GetFrameWidth() const;

protected:
	void ProcessDecay(float deltaTime);
	

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:
	bool m_dead;
protected:
	Sprite* m_pSprite;

	AnimatedSprite* m_pAnimatedSprite;
	bool m_isAnimated;
	int m_spriteSheetYPosition;
	int m_frameWidth;
	int m_frameHeight;
	int m_numAnimations; // number of rows

	Vector2 m_position;
	Vector2 m_velocity;

	b2Body* m_body;

	bool m_contacting;

	std::string m_name = "Entity";

	bool m_toSetDead;
	bool m_settingDead;
	bool m_toSetDeadValue;

	bool m_toTransformBody;
	bool m_transformingBody;
	b2Vec2 m_toTransformValue;

	bool m_toAddForce;
	bool m_addingForce;
	b2Vec2 m_toAddForceValue;

	bool m_isDecaying;
	float DECAY_TIME = 5.0f;
	float m_currentTime;
	unsigned char m_alpha;


private:

};

#endif //__ENTITY_H__
