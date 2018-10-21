// COMP710 GP 2D Framework 2018
#ifndef __GAME_H__
#define __GAME_H__
#include "Box2D/Box2D.h"
#include "Pistol.h"
#include "ObjectPool.h"
#include "SplashArt.h"
#include "ParticleEmitter.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Platform;
class Ball;
class Player;
class MainMenu;
class LevelManager;

extern float MTP;
extern float PTM;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	void InitialiseWorld();
	bool DoGameLoop();
	void Quit();

	void ProcessSplashScreen(float deltaTime);
	void ProcessMenu(float deltaTime);
	void ProcessGame(float deltaTime);

	void DrawSplashScreen(BackBuffer& backBuffer);
	void DrawMenu(BackBuffer& backBuffer);
	void DrawGame(BackBuffer& backBuffer);

	void RestartLevel();
	void ReturnToMenu();

	void MovePlayerRight();
	void MovePlayerLeft();
	void StopPlayer();
	void PlayerJump();
	void PlayerPickup();
	void SetPlayerReticleVelocity(int x, int y);
	void SetPlayerReticleXVelocity(int x);
	void SetPlayerReticleYVelocity(int y);

	void StartGameOver(bool hasWon);

	bool IsGameOver();
	bool HasWon();

	void StartNextLevel();

	MainMenu* GetMainMenu();

	void PlayerShoot();

	BackBuffer* GetBackBuffer();

	enum GameStates
	{
		SPLASH, MENU, GAME
	};

	GameStates m_currentGameState;
	int m_startingLevel;

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:


protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	b2World* m_world;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Physics Simulation Counters:
	float32 m_timeStep;
	int32 m_velocityIterations;
	int32 m_positionIterations;
	
	Player* m_player;

	ObjectPool* m_pool;

	SplashArt m_splash;

	MainMenu* m_mainMenu;

	bool m_isGameOver;	
	bool m_isGameOverWin;
	bool m_toEndGame;
	float m_endGameTimer;
	float m_endGameTime;

	bool m_toStartNextLevel;
	float m_timeToStartNextLevel;
	float m_nextLevelTimer;


private:

};

#endif // __GAME_H__
