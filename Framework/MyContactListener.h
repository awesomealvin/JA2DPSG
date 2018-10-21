#ifndef __MYCONTACTLISTENER_H__
#define __MYCONTACTLISTENER_H__
#include "Box2D\Dynamics\b2WorldCallbacks.h"
class MyContactListener :
	public b2ContactListener
{
public:
	MyContactListener();
	~MyContactListener();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
};

#endif