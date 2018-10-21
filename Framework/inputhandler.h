// COMP710 GP 2D Framework 2018
#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class Game;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessInput(Game& game);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	SDL_Joystick* m_pGameController;

	int m_leftAnalogHorizontalDeadzone;
	int m_leftAnalogVerticalDeadzone;

	int m_rightAnalogHorizontalDeadzone;
	int m_rightAnalogVerticalDeadzone;

private:

};

#endif // __INPUTHANDER_H__
