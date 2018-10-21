#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "Vector2.h"

class Sprite;
class BackBuffer;

class Button
{
public:
	Button();
	~Button();

	bool Initialise(Sprite* sprite, const char* text);
	void SetText(const char* text);
	void SetPosition(Vector2 position);

	void Draw(BackBuffer& backBuffer);

	bool IsClicked(Vector2 clickPosition);

	Vector2 m_position;

	int m_width;
	int m_height;

protected:
	Sprite* m_pSprite;

	const char* m_text;

	const int yOffset;
	int m_textXOffset;
};

#endif

