#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

#include "sprite.h"

#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);
	void SetFrameHeight(int h);

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

	int GetFrameWidth() const;
	int GetFrameHeight() const;
	int GetXCoord() const;

	void SetYCoord(int y);
	int GetYCoord() const;

	

	//std::vector GetFrameCoords

protected:

private:

	// Fields:
public:

protected:
	// W03.4: Add a field, the container for frame coordinates.
	std::vector<int> m_coordContainer;
	int m_yCoord;

	float m_frameSpeed;
	int m_frameWidth;
	int m_frameHeight;

	float m_timeElapsed;
	int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;


};

#endif // __ANIMATEDSPRITE_H__
