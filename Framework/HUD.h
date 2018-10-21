#ifndef __HUD_H__
#define __HUD_H__

#include <string>

class BackBuffer;

class HUD
{
public:
	static HUD& GetInstance();
	static void DestroyInstance();
	~HUD();

	void Initialise();

	void Draw(BackBuffer& backBuffer);

	void SetGameOverText(std::string text);
	void SetCurrentLevelText(int currentLevel);
	void SetEnemiesRemainingText(int enemiesRemaining);

	bool m_isGameOver;
	bool m_isGameOverWin;

private:
	HUD();
	HUD(const HUD& hud);
	HUD& operator=(const HUD& hud);

protected:
	static HUD* sm_pInstance;

	std::string m_gameOver;
	std::string m_gameOverSubtitle;
	std::string m_gameOverSubtitleWin;

	std::string m_currentLevel;
	std::string m_enemiesRemaining;

	

};

#endif