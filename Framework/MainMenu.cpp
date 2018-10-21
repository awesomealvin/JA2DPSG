#include "MainMenu.h"

#include "backbuffer.h"
#include "sprite.h"
#include "game.h"
#include "logmanager.h"
#include <string>

MainMenu::MainMenu()
	: NUMBER_OF_BUTTONS(3)
	, MENU_TITLE("JA2DPSG")
	, MENU_SUBTITLE("Just Another 2D Platformer Shooter Game")
	, CENTER_X(640)
	, CENTER_Y(360)
{
}



MainMenu::~MainMenu()
{
	delete sprite;
	sprite = 0;

	delete[] m_buttons;
	m_buttons = 0;
}

void MainMenu::Initialise(BackBuffer & backBuffer)
{
	m_menuState = MenuStates::MAIN_SCREEN;
	
	sprite = backBuffer.CreateSprite("..\\bin\\assets\\button.png");
	m_buttons = new Button[NUMBER_OF_BUTTONS];


	// --- BUTTONS --- //
	m_buttons[START_GAME].Initialise(sprite, "START GAME");
	m_buttons[HOW_TO_PLAY].Initialise(sprite, "HOW TO PLAY");
	m_buttons[EXIT].Initialise(sprite, "QUIT GAME");

	// --- BUTTON PLACING --- //
	int offsetCenterX = m_buttons[0].m_width / 2;
	int offsetCenterY = m_buttons[0].m_height / 2;
	
	int spacing = 60;
	//int numberOfButtons = sizeof(NUMBER_OF_BUTTONS);

	int height = (spacing * (NUMBER_OF_BUTTONS - 1)) * NUMBER_OF_BUTTONS;

	int buttonPanelYOffset = 100;
	int startingY = (CENTER_Y - (height / 2) + buttonPanelYOffset);
	int currentY = startingY + spacing;
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
	{
		Vector2 pos;
		pos.m_x = static_cast<float>(CENTER_X - offsetCenterX);
		pos.m_y = static_cast<float>(currentY);
		m_buttons[i].SetPosition(pos);

		currentY += spacing;
	}
	
	// --- INSTRUCTIONS MENU --- //
	CreateHowToPlayStrings();
	m_backButton.Initialise(sprite, "BACK");
	Vector2 backPosition;
	backPosition.m_x = static_cast<float>(CENTER_X - offsetCenterX);
	backPosition.m_y = 600.0f;
	m_backButton.SetPosition(backPosition);
}

void MainMenu::CheckClick(Vector2 position)
{
	
	if (m_menuState == MenuStates::MAIN_SCREEN)
	{
		std::string debug = "x = ";
		debug += std::to_string(position.m_x) + " | y = " + std::to_string(position.m_y);
		LogManager::GetInstance().Log(debug.c_str());

		if (m_buttons[START_GAME].IsClicked(position))
		{
			Game::GetInstance().m_currentGameState = Game::GameStates::GAME;
			Game::GetInstance().RestartLevel();
		}
		else if (m_buttons[HOW_TO_PLAY].IsClicked(position))
		{
			// How to play menu;
			m_menuState = MenuStates::INSTRUCTIONS_SCREEN;
		}
		else if (m_buttons[EXIT].IsClicked(position))
		{
			Game::GetInstance().Quit();
		}
	}
	else if (m_menuState == MenuStates::INSTRUCTIONS_SCREEN)
	{
		if (m_backButton.IsClicked(position))
		{
			m_menuState = MenuStates::MAIN_SCREEN;
		}
	}
	
}

void MainMenu::Draw(BackBuffer& backBuffer)
{
	LogManager::GetInstance().Log((std::to_string(static_cast<int>(m_menuState)).c_str()));
	if (m_menuState == MenuStates::MAIN_SCREEN)
	{
		for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
		{
			m_buttons[i].Draw(backBuffer);
		}

		// Draw Title
		int x = CENTER_X;
		int y = CENTER_Y;
		backBuffer.DrawTitleText(x, 100, MENU_TITLE, true);
		backBuffer.DrawSubtitleText(x, 175, MENU_SUBTITLE, true);
	} 
	else if (m_menuState == MenuStates::INSTRUCTIONS_SCREEN)
	{
		backBuffer.DrawInstructionsText(75, 75, m_controls.c_str(), false);
		backBuffer.DrawInstructionsText(600, 75, m_howToPlay.c_str(), false);

		m_backButton.Draw(backBuffer);
	}
	
}

void MainMenu::CreateHowToPlayStrings()
{
	m_controls = "CONTROLS: \n";
	m_controls += "Mouse + Keyboard:\n";
	m_controls += "Left Mouse - Aim\n";
	m_controls += "Left Mouse Button - Shoot\n";
	m_controls += "A - Move Left\n";
	m_controls += "D - Move Right\n";
	m_controls += "Space - Jump\n";
	m_controls += "E - Pickup/Throw Weapon\n";
	m_controls += "P - Restart Current Level\n";
	m_controls += "L - Show Debug Hitboxes \n";
	m_controls += "ESC - Return to Main Menu \n";
	m_controls += "-----------------------------\n";
	m_controls += "Xbox360 Controller:\n";
	m_controls += "Right Analog - Aim\n";
	m_controls += "Right Trigger - Shoot\n";
	m_controls += "Left Analog - Move Left/Right\n";
	m_controls += "Left Trigger - Jump\n";
	m_controls += "A - Pickup/Throw\n";
	m_controls += "Back Button - Restart Current Level\n";

	m_howToPlay = "How To Play:\n";
	m_howToPlay += " - Shoot your way through 10 levels full of enemies.\n";
	m_howToPlay += " - Be extra careful though, as you will die in one shot...\n";
	m_howToPlay += " - But don't worry, enemies also die in one shot.\n";
	m_howToPlay += " - Good luck, and have fun!\n";
	m_howToPlay += " - Oh, and... Not recommended to play with controllers...\n";
}
