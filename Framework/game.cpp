// COMP710 GP 2D Framework 2018

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "Box.h"
#include "Platform.h"
#include "Vector2.h"
#include "Ball.h"
#include "Pistol.h"
#include "MyContactListener.h"
#include "MyUtility.h"
#include "Blackboard.h"
#include "EnemyStillState.h"
#include "EnemyDeadState.h"
#include "EnemyAimingState.h"
#include "EnemyFindWeaponState.h"
#include "EnemyFollowPlayerState.h"
#include "SoundManager.h"
#include "SplashArt.h"
#include "EnemyDeathParticleSystem.h"
#include "ParticleEmitter.h"
#include "Player.h"
#include "LevelManager.h"
#include "MainMenu.h"
#include "DebugUI.h"
#include "HUD.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <string>

#include "Box2D\Box2D.h"

// Static Members:
Game* Game::sm_pInstance = 0;

float MTP;
float PTM;

MyContactListener myContactListenerInstance;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, m_currentGameState(GameStates::SPLASH)
	, m_startingLevel(0)
	, m_isGameOver(false)
	, m_toEndGame(false)
	, m_isGameOverWin(false)
	, m_endGameTime(0.125f)
	, m_endGameTimer(0.0f)
	, m_toStartNextLevel(false)
	, m_timeToStartNextLevel(1.0f)
	, m_nextLevelTimer(0.0f)
{


}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	LogManager::DestroyInstance();
	ObjectPool::DestroyInstance();
	MyUtility::DestroyInstance();

	EnemyStillState::DestroyInstance();
	EnemyDeadState::DestroyInstance();
	EnemyAimingState::DestroyInstance();
	EnemyFindWeaponState::DestroyInstance();
	EnemyFollowPlayerState::DestroyInstance();
	Blackboard::DestroyInstance();

	EnemyDeathParticleSystem::DestroyInstance();

	SoundManager::DestroyInstance();

	ParticleEmitter::DestroyInstance();

	DebugUI::DestroyInstance();

	LevelManager::DestroyInstance();

	HUD::DestroyInstance();

	delete m_mainMenu;
	m_mainMenu = 0;

	delete m_world;
	m_world = 0;

	delete m_player;
	m_player = 0;

	/*delete m_levelManager;
	m_levelManager = 0;*/

}

bool
Game::Initialise()
{
	const int width = 1280;
	const int height = 720;

	MTP = 60.0f;
	PTM = 1 / MTP;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// W02.1: Load the player ship sprite.
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	InitialiseWorld();

	Sprite* playerSprite = m_pBackBuffer->CreateSprite("..\\bin\\assets\\player.png");
	m_player = new Player();
	m_player->Initialise(playerSprite, *m_pBackBuffer);
	m_player->InitialiseBody(m_world, Vector2(400, 550));

	m_pool = &ObjectPool::GetInstance();
	m_pool->Initialise(m_pBackBuffer, m_world);

	LevelManager::GetInstance().Initialise(*m_player, m_startingLevel);
	LevelManager::GetInstance().ResetLevel(m_startingLevel, *m_player);
	//InitialisePlatforms();

	SoundManager::GetInstance().Initialise();
	ParticleEmitter::GetInstance().Initialise(*m_pBackBuffer);

	Sprite* sprite = m_pBackBuffer->CreateSprite("..\\bin\\assets\\splash_art.png");
	m_splash.Initialise(sprite);

	m_mainMenu = new MainMenu();
	m_mainMenu->Initialise(*m_pBackBuffer);

	HUD::GetInstance().Initialise();

	return (true);
}

void Game::InitialiseWorld()
{
	// Gravity
	b2Vec2 gravity(0.0f, 9.81f);

	// Initialise World
	m_world = new b2World(gravity);

	m_timeStep = 1.0f / 60.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;

	m_world->SetContactListener(&myContactListenerInstance);
}


bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{

			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}

		Draw(*m_pBackBuffer);


	}

	//	SDL_Delay(1);

	return (m_looping);
}


void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	switch (m_currentGameState)
	{
	case GameStates::SPLASH: ProcessSplashScreen(deltaTime);
		break;
	case GameStates::MENU: ProcessMenu(deltaTime);
		break;
	case GameStates::GAME: ProcessGame(deltaTime);
		break;
	}


	SoundManager::GetInstance().Update();
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	switch (m_currentGameState)
	{
	case GameStates::SPLASH: DrawSplashScreen(backBuffer);
		break;
	case GameStates::MENU: DrawMenu(backBuffer);
		break;
	case GameStates::GAME: DrawGame(backBuffer);
		break;
	}


	// W02.2: Draw all enemy aliens in container...

	// W02.3: Draw all bullets in container...

	// W02.1: Draw the player ship...

	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void Game::ProcessSplashScreen(float deltaTime)
{
	m_splash.Process(deltaTime);
	if (!m_splash.isEnabled)
	{
		m_currentGameState = GameStates::MENU;
	}
}

void Game::ProcessMenu(float deltaTime)
{

}

void Game::ProcessGame(float deltaTime)
{
	if (!m_isGameOver)
	{
		m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);

		m_player->Process(deltaTime);
		m_pool->Process(deltaTime);

		ParticleEmitter::GetInstance().Process(deltaTime);

		DebugUI::GetInstance().SetLine(0, "Current FPS: " + std::to_string(m_FPS));
	}

	if (m_toEndGame)
	{
		m_endGameTimer += deltaTime;
		if (m_endGameTimer > m_endGameTime)
		{
			m_isGameOver = true;
			m_toEndGame = false;

			HUD::GetInstance().m_isGameOver = true;
			HUD::GetInstance().m_isGameOverWin = m_isGameOverWin;
		}
	}

	if (m_toStartNextLevel)
	{
		m_nextLevelTimer += deltaTime;
		if (m_nextLevelTimer >= m_timeToStartNextLevel)
		{
			m_toStartNextLevel = false;
			m_nextLevelTimer = 0.0f;
			RestartLevel();
		}
	}


}

void Game::DrawSplashScreen(BackBuffer & backBuffer)
{
	m_splash.Draw(backBuffer);
}

void Game::DrawMenu(BackBuffer & backBuffer)
{
	m_mainMenu->Draw(backBuffer);
}

void Game::DrawGame(BackBuffer & backBuffer)
{
	backBuffer.SetClearColour(100, 100, 100);
	m_player->Draw(backBuffer);
	m_pool->Draw(backBuffer);

	ParticleEmitter::GetInstance().Draw(backBuffer);

	//DebugUI::GetInstance().Draw(backBuffer);

	backBuffer.SetTextColor(220, 220, 220);
	HUD::GetInstance().Draw(backBuffer);

}

void Game::RestartLevel()
{
	m_isGameOver = false;
	m_isGameOverWin = false;
	LevelManager::GetInstance().ResetLevel(*m_player);
	HUD::GetInstance().m_isGameOver = false;
	HUD::GetInstance().m_isGameOverWin = false;
}

void Game::ReturnToMenu()
{
	HUD::GetInstance().m_isGameOver = false;
	HUD::GetInstance().m_isGameOverWin = false;
	m_isGameOver = false;
	m_currentGameState = MENU;
	LevelManager::GetInstance().ClearLevel();
}


void Game::MovePlayerRight()
{
	m_player->MoveRight();
}

void Game::MovePlayerLeft()
{
	m_player->MoveLeft();
}

void Game::StopPlayer()
{
	m_player->Stop();
}

void Game::PlayerJump()
{
	m_player->Jump();
}

void Game::PlayerPickup()
{
	m_player->Pickup();
}

void Game::SetPlayerReticleVelocity(int x, int y)
{
	Vector2 velocity;
	velocity.m_x = static_cast<float>(x);
	velocity.m_y = static_cast<float>(y);
	m_player->SetReticleVelocity(velocity);
}

void Game::SetPlayerReticleXVelocity(int x)
{
	m_player->SetReticleXVelocity(x);
}

void Game::SetPlayerReticleYVelocity(int y)
{
	m_player->SetReticleYVelocity(y);
}



void Game::StartGameOver(bool hasWon)
{
	m_toEndGame = true;
	m_isGameOverWin = hasWon;
	m_endGameTimer = 0.0f;
}

bool Game::IsGameOver()
{
	return m_isGameOver;
}

bool Game::HasWon()
{
	return m_isGameOverWin;
}

void Game::StartNextLevel()
{
	m_toStartNextLevel = true;
	m_nextLevelTimer = 0.0f;
}

MainMenu* Game::GetMainMenu()
{
	return m_mainMenu;
}

void Game::PlayerShoot()
{
	m_player->Shoot();
}



BackBuffer * Game::GetBackBuffer()
{
	return m_pBackBuffer;
}

