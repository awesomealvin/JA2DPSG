#include "SplashArt.h"
#include "sprite.h"
#include "logmanager.h"
#include <string>

SplashArt::~SplashArt()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool SplashArt::Initialise(Sprite * sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	
	m_pSprite->SetX(0);
	m_pSprite->SetY(0);
	
	t = 0.0f;

	isEnabled = true;
	fadeIn = true;
	fadeOut = false;

	alpha = 0;

	return (true);
}

void SplashArt::Process(float deltaTime)
{
	if (fadeIn)
	{
		alpha = static_cast<unsigned char>(MyUtility::Lerp(0, 255, t));
		t += deltaTime / (FADE_TIME * 1.5f);

		if (t >= 1.0f)
		{
			fadeIn = false;
			fadeOut = true;
			t = 0;
		}
	}

	if (fadeOut)
	{
		alpha = static_cast<unsigned char>(MyUtility::Lerp(255, 0, t));
		t += deltaTime / FADE_TIME;

		if (t >= 1.0f)
		{
			fadeOut = false;
		}
	}

	if (!fadeOut && !fadeIn)
	{
		isEnabled = false;
	}


}

void SplashArt::Draw(BackBuffer & backBuffer)
{
	if (fadeIn)
	{
		backBuffer.SetClearColour(0, 0, 0);
	}
	else
	{
		backBuffer.SetClearColour(255, 255, 255);
	}
	//LogManager::GetInstance().Log(std::to_string(alpha).c_str());
	backBuffer.SetAlpha(*m_pSprite, alpha);
	backBuffer.DrawSprite(*m_pSprite);
}
