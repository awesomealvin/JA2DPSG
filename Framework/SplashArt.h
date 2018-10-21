#ifndef __SPLASHART_H__
#define __SPLASHART_H__

#include "backbuffer.h"
#include "MyUtility.h"


class SplashArt
{
public:
	~SplashArt();

	const float FADE_TIME = 2.5f;
	float t;

	bool isEnabled;
	bool fadeIn;
	bool fadeOut;

	unsigned char alpha;

	Sprite* m_pSprite;

	bool Initialise(Sprite* sprite);


	void Process(float deltaTime);
	

	void Draw(BackBuffer& backBuffer);

};

#endif
