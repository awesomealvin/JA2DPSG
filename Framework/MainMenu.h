#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "Vector2.h"
#include <string>
#include "Button.h"


class BackBuffer;
class Sprite;


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Initialise(BackBuffer& backBuffer);
	void CheckClick(Vector2 position);

	void Draw(BackBuffer& backBuffer);


	enum ButtonType
	{
		START_GAME = 0,
		HOW_TO_PLAY = 1,
		EXIT = 2
	};

	enum class MenuStates
	{
		MAIN_SCREEN,
		INSTRUCTIONS_SCREEN
	};

	

protected:
	Sprite* sprite;
	Button* m_buttons;
	const int NUMBER_OF_BUTTONS;
	const int CENTER_X;
	const int CENTER_Y;

	const char* MENU_TITLE;
	const char* MENU_SUBTITLE;

	void CreateHowToPlayStrings();
	std::string m_controls;
	std::string m_howToPlay;
	Button m_backButton;
	
	MenuStates m_menuState;
};

#endif
