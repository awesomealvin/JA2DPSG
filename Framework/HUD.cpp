#include "HUD.h"
#include "backbuffer.h"

HUD* HUD::sm_pInstance = 0;


void HUD::SetGameOverText(std::string text)
{
	m_gameOver = std::string("GAME OVER: ").append(text);
}

void HUD::SetCurrentLevelText(int currentLevel)
{
	std::string addon = std::to_string(currentLevel);
	m_currentLevel = std::string("Current Level: ").append(addon);
}

void HUD::SetEnemiesRemainingText(int enemiesRemaining)
{
	std::string addon = std::to_string(enemiesRemaining);
	m_enemiesRemaining = std::string("Enemies Remaining: ").append(addon);
}

HUD::HUD()
	: m_isGameOver(false)
	, m_isGameOverWin(false)
{
}


HUD & HUD::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new HUD();
	}

	return (*sm_pInstance);
}

void HUD::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

HUD::~HUD()
{
}

void HUD::Draw(BackBuffer & backBuffer)
{
	backBuffer.DrawHUDText(50, 100, m_currentLevel.c_str(), false);
	backBuffer.DrawHUDText(900, 100, m_enemiesRemaining.c_str(), false);

	if (m_isGameOver)
	{
		if (m_isGameOverWin)
		{
			backBuffer.SetTextColor(0, 255, 0);
			backBuffer.DrawTitleText(640, 300, m_gameOver.c_str(), true);
			backBuffer.DrawSubtitleText(640, 400, m_gameOverSubtitleWin.c_str(), true);
		}
		else
		{
			backBuffer.SetTextColor(255, 0, 0);
			backBuffer.DrawTitleText(640, 300, m_gameOver.c_str(), true);
			backBuffer.DrawSubtitleText(640, 400, m_gameOverSubtitle.c_str(), true);
		}
	}
}


void HUD::Initialise()
{
	m_gameOver = "GAME OVER: YOU DIED";
	m_gameOverSubtitle = "Click to restart level. Press ESC to QUIT";
	m_gameOverSubtitleWin = "Press ESC to quit.";
}
