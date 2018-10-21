// COMP710 GP 2D Framework 2018

// This include:
#include "inputhandler.h"
#include "DebugUI.h"

// Local includes:
#include "game.h"
#include "logmanager.h"
#include "MainMenu.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
	: m_pGameController(0)
	, m_leftAnalogHorizontalDeadzone(10000)
	, m_leftAnalogVerticalDeadzone(10000)
	, m_rightAnalogHorizontalDeadzone(20000)
	, m_rightAnalogVerticalDeadzone(20000)
{

}

InputHandler::~InputHandler()
{
	if (!m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}


// TODO: Put in header
bool movementAKeyDown = false;
bool movementDKeyDown = false;

void
InputHandler::ProcessInput(Game& game)
{
	// W02.1: Receive Input Events below...
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (game.m_currentGameState == Game::GameStates::GAME)
		{
			if (e.type == SDL_QUIT)
			{
				game.Quit();
			}
			else if (e.type == SDL_JOYBUTTONDOWN)
			{
				// ONLY TESTED WITH STEAM CONTROLLER WITH XBOX360 CONFIGURATION
				// 0 = A
				// 2 = X
				// 1 = B
				// 3 = Y
				int buttonNumber = e.jbutton.button;
				std::string debug = "SDL_JOYBUTTONDOWN: " + std::to_string(buttonNumber);
				if (e.jbutton.button == 0)
				{
					// A BUTTON
					// Pickup/Throw Key
					debug.append(": A Pressed");
					game.PlayerPickup();

				}
				else if (e.jbutton.button == 2)
				{
					// X BUTTON
					debug.append(": X Pressed");
				}
				else if (e.jbutton.button == 1)
				{
					// B BUTTON
					debug.append(": B Pressed");
				}
				else if (e.jbutton.button == 3)
				{
					// Y BUTTON
					debug.append(": Y Pressed");
				}
				else if (e.jbutton.button == 6)
				{
					// Select button?!
					game.RestartLevel();
				}

				//DebugUI::GetInstance().SetLine(1, debug);

			}
			else if (e.type == SDL_JOYAXISMOTION)

			{

				std::string debug = "STDL_JOYAXISMOTION: ";
				debug.append(std::to_string(e.jaxis.axis));
				debug.append(" | Value: " + std::to_string(e.jaxis.value));

				std::string debug2 = "Controller Movement: ";
				int deadzoneHorizontal = 3000;
				int deadzoneVertical = 10000;

				if (e.jaxis.axis == 0) // 0 == x | 1 == y
				{
					if (e.jaxis.value < -m_leftAnalogHorizontalDeadzone)
					{
						debug2.append("Left");
						game.MovePlayerLeft();
					}
					else if (e.jaxis.value > m_leftAnalogHorizontalDeadzone)

					{
						debug2.append("Right");
						game.MovePlayerRight();
					}
					else
					{
						game.StopPlayer();
					}
					//DebugUI::GetInstance().SetLine(3, debug2);
				}
				else if (e.jaxis.axis == 1)
				{
					if (e.jaxis.value < -m_leftAnalogVerticalDeadzone)
					{
						debug2.append("Up");

					}
					else if (e.jaxis.value > m_leftAnalogVerticalDeadzone)
					{
						debug2.append("Down");
					}
				}
				//DebugUI::GetInstance().SetLine(2, debug);
				std::string directionDebug = "Controller Aiming: ";

				int xVel = 0;
				int yVel = 0;
				if (e.jaxis.axis == 3) // Right Analog Y Axis
				{
					if (e.jaxis.value < -m_rightAnalogHorizontalDeadzone)
					{
						directionDebug.append("Left");

					}
					else if (e.jaxis.value > m_rightAnalogHorizontalDeadzone)
					{
						directionDebug.append("Right");
					}
					//DebugUI::GetInstance().SetLine(4, directionDebug);
					//DebugUI::GetInstance().SetLine(4, directionDebug);
					game.SetPlayerReticleXVelocity(e.jaxis.value);

				}
				if (e.jaxis.axis == 4)
				{
					if (e.jaxis.value < -m_rightAnalogVerticalDeadzone)
					{
						directionDebug.append("Up");
					}
					else if (e.jaxis.value > m_rightAnalogVerticalDeadzone)
					{
						directionDebug.append("Down");

					}
					//DebugUI::GetInstance().SetLine(5, directionDebug);
					game.SetPlayerReticleYVelocity(e.jaxis.value);
				}

				if (e.jaxis.axis == 2)
				{
					// Left Trigger

					if (e.jaxis.value > 32000)
					{
						game.PlayerJump();
					}
				}
				if (e.jaxis.axis == 5)
				{
					// Right Trigger
					if (e.jaxis.value > 32000)
					{
						game.PlayerShoot();
					}
				}

			}
			else if (e.type == SDL_KEYDOWN)
			{
				// A Key
				if (e.key.keysym.sym == SDLK_a)
				{
					game.MovePlayerLeft();
					movementAKeyDown = true;

					//DebugUI::GetInstance().SetLine(0, "Moving Left");
				}

				if (e.key.keysym.sym == SDLK_d)
				{
					game.MovePlayerRight();
					movementDKeyDown = true;
					//DebugUI::GetInstance().SetLine(0, "Moving Right");
				}

				if (e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0)
				{
					game.PlayerJump();
					//DebugUI::GetInstance().SetLine(0, "Jumped");

				}

				// E: Pickup Key
				if (e.key.keysym.sym == SDLK_e && e.key.repeat == 0)
				{

					game.PlayerPickup();
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				// A Key
				if (e.key.keysym.sym == SDLK_a)
				{
					movementAKeyDown = false;

					if (!movementDKeyDown) {
						game.StopPlayer();
					}

				}

				if (e.key.keysym.sym == SDLK_d)
				{
					movementDKeyDown = false;

					if (!movementAKeyDown) {
						game.StopPlayer();
					}
				}

				// Restart Current Level
				if (e.key.keysym.sym == SDLK_p)
				{
					game.RestartLevel();
				}

				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					game.ReturnToMenu();
				}

				if (e.key.keysym.sym == SDLK_l)
				{
					DebugUI::GetInstance().m_drawHitBoxes = !DebugUI::GetInstance().m_drawHitBoxes;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					game.PlayerShoot();
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (game.IsGameOver())
				{
					game.RestartLevel();

				}
			}
		}
		else if (game.m_currentGameState == Game::GameStates::MENU)
		{
			// --- MENU CONTROLS HERE -- //
			if (e.type == SDL_QUIT)
			{
				game.Quit();
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{

					Vector2 mousePos;
					mousePos.m_x = static_cast<float>(e.button.x);
					mousePos.m_y = static_cast<float>(e.button.y);
					game.GetMainMenu()->CheckClick(mousePos);
				}
			}
		}

	}

}
