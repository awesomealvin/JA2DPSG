#include "MyContactListener.h"
#include "Box2D/Box2D.h"
#include "entity.h"

#include "logmanager.h"

MyContactListener::MyContactListener()
{
}


MyContactListener::~MyContactListener()
{
}

void MyContactListener::BeginContact(b2Contact * contact)
{
	//LogManager::GetInstance().Log("HEY LOOK I HIT SOMETHING");
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyAUserData && bodyBUserData)
	{
		Entity* a = static_cast<Entity*>(bodyAUserData);
		Entity* b = static_cast<Entity*>(bodyBUserData);
		
		a->OnCollisionBegin(b, contact);
		b->OnCollisionBegin(a, contact);
	}
}

void MyContactListener::EndContact(b2Contact * contact)
{

}

void MyContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyAUserData && bodyBUserData)
	{
		Entity* a = static_cast<Entity*>(bodyAUserData);
		Entity* b = static_cast<Entity*>(bodyBUserData);

		a->OnCollisionPostSolve(b, contact, impulse);
		b->OnCollisionPostSolve(a, contact, impulse);
	}
}

void MyContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

	if (bodyAUserData && bodyBUserData)
	{
		Entity* a = static_cast<Entity*>(bodyAUserData);
		Entity* b = static_cast<Entity*>(bodyBUserData);

		a->OnCollisionPreSolve(b, contact, oldManifold);
		b->OnCollisionPreSolve(a, contact, oldManifold);
	}
}
