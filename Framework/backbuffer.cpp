// COMP710 GP 2D Framework 2018

// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "texturemanager.h"
#include "sprite.h"
#include "texture.h"
#include "MyUtility.h"
#include "game.h"
#include "Box2D/Box2D.h"
#include "animatedsprite.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

BackBuffer::BackBuffer()
	: m_pTextureManager(0)
	, m_pWindow(0)
	, m_pRenderer(0)
	, m_width(0)
	, m_height(0)
	, m_clearRed(0xFF)
	, m_clearGreen(0xFF)
	, m_clearBlue(0xFF)
	, m_textRed(255)
	, m_textGreen(0)
	, m_textBlue(0)
{
}

BackBuffer::~BackBuffer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	delete m_pTextureManager;
	m_pTextureManager = 0;

	IMG_Quit();
	SDL_Quit();
}

bool
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("COMP710 2D Game Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
			}
		}
	}

	TTF_Init();
	m_pMenuFont = TTF_OpenFont("..\\bin\\assets\\fonts\\absender1.ttf", 20);
	m_pTitleFont = TTF_OpenFont("..\\bin\\assets\\fonts\\absender1.ttf", 100);
	m_pSubtitleFont = TTF_OpenFont("..\\bin\\assets\\fonts\\absender1.ttf", 17);
	m_pInstructionsFont = TTF_OpenFontIndex("..\\bin\\assets\\fonts\\Avenir.ttc", 20, 4);
	m_pHUDFont = TTF_OpenFont("..\\bin\\assets\\fonts\\absender1.ttf", 32);

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	

	return (true);
}

void
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void BackBuffer::SetAlpha(Sprite & sprite, unsigned char alpha)
{
	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(),alpha);
}

void
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest);
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;

	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2;
	fillRect.h = y2;
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);
	SDL_RenderFillRect(m_pRenderer, &fillRect);

}

void BackBuffer::DrawRectangle2(int x1, int y1, int width, int height)
{
	SDL_Point points[5];

	points[0].x = -(width / 2) + x1;
	points[0].y = (height / 2) + y1;

	points[1].x = (width / 2) + x1;
	points[1].y = (height / 2) + y1;

	points[2].x = (width / 2) + x1;
	points[2].y = -(height / 2) + y1;

	points[3].x = -(width / 2) + x1;
	points[3].y = -(height / 2) + y1;

	points[4].x = -(width / 2) + x1;
	points[4].y = -(height / 2) + y1;

	SDL_RenderDrawLines(m_pRenderer, points, 5);

}

void BackBuffer::DrawHitBox(b2Vec2* v, int x, int y, float angle)
{
	SDL_Point points[5];

	float radians = MyUtility::GetInstance().ToRadians(angle);

	for (int i = 0; i < 4; ++i) {

		float newX = (v[i].x * MTP);
		float newY = (v[i].y * MTP);

		points[i].x = static_cast<int>((newX)* cos(angle) - (newY)* sin(angle));
		points[i].y = static_cast<int>((newX)* sin(angle) + (newY)* cos(angle));

		points[i].x += x;
		points[i].y += y;
	}

	points[4] = points[0];

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);

	SDL_RenderDrawLines(m_pRenderer, points, 5);
}

void BackBuffer::DrawSpriteRotation(Sprite & sprite, float angle, int x, int y)
{
	DrawSpriteRotation(sprite, angle, x, y, false);
}

void BackBuffer::DrawSpriteRotation(Sprite & sprite, float angle, int x, int y, bool flip)
{
	DrawSpriteRotation(sprite, angle, x, y, Vector2(static_cast<float>(sprite.GetWidth()/2), static_cast<float>(sprite.GetHeight()/2)) ,flip);
}

void BackBuffer::DrawSpriteRotation(Sprite & sprite, float angle, int x, int y, Vector2 center, bool flip)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	float angleDegrees = MyUtility::GetInstance().ToAngle(angle);

	SDL_RendererFlip flipState;
	if (flip) 
	{
		flipState = SDL_FLIP_VERTICAL;
	}
	else 
	{
		flipState = SDL_FLIP_NONE;
	}

	SDL_Point p;
	p.x = static_cast<int>(center.m_x);
	p.y = static_cast<int>(center.m_y);
	

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, angleDegrees, &p, flipState);
}

void BackBuffer::DrawSpriteBall(Sprite & sprite, float angle, int x, int y, int radius)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	dest.w = radius * 2;
	dest.h = radius * 2;

	float angleDegrees = MyUtility::GetInstance().ToAngle(angle);

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, angleDegrees, NULL, SDL_FLIP_NONE);
}

void BackBuffer::DrawAnimatedSprite(AnimatedSprite & animatedSprite)
{
	SDL_Rect sest;
	sest.x = animatedSprite.GetXCoord();
	sest.y = animatedSprite.GetYCoord();
	sest.w = animatedSprite.GetFrameWidth();
	sest.h = animatedSprite.GetFrameHeight();

	SDL_Rect dest;
	dest.x = animatedSprite.GetX();
	dest.y = animatedSprite.GetY();
	dest.w = animatedSprite.GetFrameWidth();
	dest.h = animatedSprite.GetFrameHeight();


	SDL_RenderCopy(m_pRenderer, animatedSprite.GetTexture()->GetTexture(), &sest, &dest);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void BackBuffer::DrawCircle(int x1, int y1, int radius, float angle)
{
	const int POINT_COUNT = 360;
	SDL_Point points[POINT_COUNT + 1];

	MyUtility util = MyUtility::GetInstance();

	float angleDegrees = util.ToAngle(angle);

	// Set the center
	points[0].x = x1;
	points[0].y = y1;

	float difference = POINT_COUNT / 360;
	float currentAngle = angleDegrees;


	for (int i = 1; i <= POINT_COUNT; ++i)
	{
		float radians = util.ToRadians(currentAngle);

		float x = radius * cos(radians);
		float y = radius * sin(radians);

		x += x1;
		y += y1;

		currentAngle += static_cast<float>(fmod(difference, 360));

		points[i].x = static_cast<int>(x);
		points[i].y = static_cast<int>(y);
	}
	//points[POINT_COUNT + 1].x = points[POINT_COUNT].x;
	//points[POINT_COUNT + 1].y = points[POINT_COUNT].y;

	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, 255);


	SDL_RenderDrawLines(m_pRenderer, points, POINT_COUNT);
}

void BackBuffer::SetTextColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_textRed = r;
	m_textGreen = g;
	m_textBlue = b;
}

void BackBuffer::DrawText(int x, int y, const char * pcText, bool center, TTF_Font* font)
{
	SDL_Color color;
	color.r = m_textRed;
	color.g = m_textGreen;
	color.b = m_textBlue;
	color.a = 255;

	//SDL_Surface* surface = TTF_RenderText_Solid(font, pcText, color);
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, pcText, color, 1280);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);
	
	int width;
	int height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);


	SDL_Rect destRect;
	destRect.x = (center)?(x - (width/2)) : (x);
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(m_pRenderer, texture, 0, &destRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	
}

void BackBuffer::DrawMenuText(int x, int y, const char * pcText, bool center)
{
	DrawText(x, y, pcText, center, m_pMenuFont);
}

void BackBuffer::DrawTitleText(int x, int y, const char * pcText, bool center)
{
	DrawText(x, y,pcText, center, m_pTitleFont);
}

void BackBuffer::DrawSubtitleText(int x, int y, const char * pcText, bool center)
{
	DrawText(x, y, pcText, center, m_pSubtitleFont);
}

void BackBuffer::DrawHUDText(int x, int y, const char * pcText, bool center)
{
	DrawText(x, y, pcText, center, m_pHUDFont);

}

void BackBuffer::DrawInstructionsText(int x, int y, const char * pcText, bool center)
{
	DrawText(x, y, pcText, center, m_pInstructionsFont);
}

void
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite*
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

AnimatedSprite * BackBuffer::CreateAnimatedSprite(const char * pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	AnimatedSprite* pSprite = new AnimatedSprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

void
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}
