// COMP710 GP 2D Framework 2018
#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include "SDL_ttf.h"
#include "Vector2.h"

// Forward Declarations:
class TextureManager;
class Sprite;
class AnimatedSprite;
struct b2Vec2;
struct SDL_Window;
struct SDL_Renderer;

class BackBuffer
{
	//Member Methods:
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetAlpha(Sprite& sprite, unsigned char alpha);

	void DrawSprite(Sprite& sprite);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawRectangle2(int x1, int y1, int width, int height);
	void DrawHitBox(b2Vec2* v, int x, int y, float angle);
	void DrawSpriteRotation(Sprite & sprite, float angle, int x, int y);
	void DrawSpriteRotation(Sprite & sprite, float angle, int x, int y, bool flip);
	void DrawSpriteRotation(Sprite & sprite, float angle, int x, int y, Vector2 center, bool flip);
	void DrawSpriteBall(Sprite & sprite, float angle, int x, int y, int radius);
	void DrawAnimatedSprite(AnimatedSprite& animatedSprite);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawCircle(int x1, int y1, int radius, float angle);

	void SetTextColor(unsigned char r, unsigned char g, unsigned char b);
	void DrawText(int x, int y, const char* pcText, bool center, TTF_Font* font);
	void DrawMenuText(int x, int y, const char* pcText, bool center);
	void DrawTitleText(int x, int y, const char* pcText, bool center);
	void DrawSubtitleText(int x, int y, const char* pcText, bool center);
	void DrawHUDText(int x, int y, const char* pcText, bool center);
	void DrawInstructionsText(int x, int y, const char* pcText, bool center);


	Sprite* CreateSprite(const char* pcFilename);
	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);

	
protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	//Member Data:
public:

protected:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;

	TTF_Font* m_pMenuFont;
	unsigned char m_textRed;
	unsigned char m_textGreen;
	unsigned char m_textBlue;

	TTF_Font* m_pTitleFont;
	TTF_Font* m_pSubtitleFont;
	TTF_Font* m_pInstructionsFont;
	TTF_Font* m_pHUDFont;

	
private:

};

#endif // __BACKBUFFER_H__
