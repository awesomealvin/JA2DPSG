#ifndef __BLACKBOARD_H__
#define __BLACKBOARD_H__

#include "Box2D/Box2D.h"
#include <list>

class Player;
class Weapon;

class Blackboard
{
public:
	static Blackboard& GetInstance();
	~Blackboard();
	
	static void DestroyInstance();

	void SetPlayer(Player& player);
	bool HasFoundPlayer() const;
	b2Vec2 GetPlayerPosition();


private:
	Blackboard();
	Blackboard(const Blackboard& blackBoard);
	Blackboard& operator=(const Blackboard& blackboard);


protected:
	Player* m_player;
	bool m_foundPlayer;


	static Blackboard* sm_pInstance;
};

#endif

