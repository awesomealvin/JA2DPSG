#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "Box2D\Box2D.h"
#include "Vector2.h"
#include "game.h"
#include "logmanager.h"
#include "entity.h"

class BackBuffer;

class Platform : public Entity
{
public:
	Platform();
	Platform(int width, int height);
	~Platform();
	void Set(int width, int height);
	void InitialiseBody(b2World* world, Vector2 position);

	void Draw(BackBuffer& backBuffer);

	EntityTypes GetType() const;


protected:
	int m_width;
	int m_height;


private:
	/*Platform(const Platform& entity);
	Platform& operator=(const Platform& entity);*/
};

#endif