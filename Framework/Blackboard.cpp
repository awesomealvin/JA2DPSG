#include "Blackboard.h"

#include "Weapon.h"
#include "Level.h"
#include "LevelManager.h"
#include <vector>
#include "MyUtility.h"
#include "Player.h"

Blackboard* Blackboard::sm_pInstance = 0;

Blackboard & Blackboard::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Blackboard();
	}

	return (*sm_pInstance);
}

Blackboard::~Blackboard()
{

}

void Blackboard::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

void Blackboard::SetPlayer(Player & player)
{
	m_player = &player;
	if (m_player != 0)
	{
		m_foundPlayer = true;
	}
}

bool Blackboard::HasFoundPlayer() const
{
	return m_foundPlayer;
}

b2Vec2 Blackboard::GetPlayerPosition()
{
	return m_player->GetWorldPosition();
}


Blackboard::Blackboard()
{

}

