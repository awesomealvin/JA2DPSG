#include "Button.h"

#include "sprite.h"
#include "backbuffer.h"
#include "logmanager.h"
#include <string>

#include <cassert>

Button::Button()
	: m_height(0)
	, m_width(0)
	, yOffset(9)
	, m_textXOffset(0)
{

}


Button::~Button()
{
}

bool Button::Initialise(Sprite * sprite, const char * text)
{
	assert(sprite);
	m_pSprite = sprite;

	m_width = m_pSprite->GetWidth();
	m_height = m_pSprite->GetHeight();

	m_text = text;
	int textLength = strlen(m_text);
	
	//m_textXOffset = (m_width / 2);
	//m_textXOffset -= textLength * 5;
	/*
	std::string debug = "Size of: ";
	debug += text;
	debug += " = ";
	debug += std::to_string(textLength);
	LogManager::GetInstance().Log(debug.c_str());*/
	
	

	return (true);
}

void Button::SetText(const char * text)
{
	m_text = text;
}

void Button::SetPosition(Vector2 position)
{
	m_position = position;
}

void Button::Draw(BackBuffer & backBuffer)
{
	int x = static_cast<int>(m_position.m_x);
	int y = static_cast<int>(m_position.m_y);
	backBuffer.DrawSpriteRotation(*m_pSprite, 0, 
		x, y);

	backBuffer.SetTextColor(0, 0, 0);
	backBuffer.DrawMenuText(x + (m_width / 2), y + yOffset, m_text, true);
}


bool Button::IsClicked(Vector2 clickPosition)
{
	bool clicked = false;
	//LogManager::GetInstance().Log("BUTTON CLICKED");

	if (((clickPosition.m_x >=  m_position.m_x) && (clickPosition.m_x < m_width + m_position.m_x)) &&
		((clickPosition.m_y >=  m_position.m_y) && (clickPosition.m_y < m_height + m_position.m_y)))
	{
		clicked = true;
	}

	return clicked;
}
