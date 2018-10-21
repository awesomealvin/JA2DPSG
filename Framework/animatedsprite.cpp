// This includes:
#include "animatedsprite.h"
#include "logmanager.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
	, m_yCoord(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void 
AnimatedSprite::AddFrame(int x)
{
	// W03.4: Add the x coordinate to the frame coordinate container.
	m_coordContainer.push_back(x);

}

void 
AnimatedSprite::Process(float deltaTime)
{
	if (!m_animating)
	{
		return;
	}
	// W03.4: If not paused...
	// W03.4: Count the time elapsed.
	if (!m_paused)
	{
		m_timeElapsed += deltaTime;
		// For some reason the process is only called once?!
	}

	// W03.4: If the time elapsed is greater than the frame speed.
	// W03.4: Move to the next frame.
	// W03.4: Reset the time elapsed counter.
	if (m_timeElapsed >= m_frameSpeed)
	{
		++m_currentFrame;
		m_timeElapsed = 0;
	}

	// W03.4: If the current frame is greater than the number 
	//          of frame in this animation...
	// W03.4: Reset to the first frame.
	if (m_currentFrame + 1 > static_cast<int>(m_coordContainer.size()))
	{
		m_currentFrame = 0;

		// W03.4: Stop the animation if it is not looping...
		if (!m_loop)
		{
			m_animating = false;
		}
	}
	
}

void 
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	if (!m_animating)
	{
		return;
	}
	// W03.4: Draw the particular frame into the backbuffer.
	backbuffer.DrawAnimatedSprite(*this);
	//          What is the current frame's x coordinate?
	//          What is the frame width?
}

void 
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void 
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void AnimatedSprite::SetFrameHeight(int h)
{
	m_frameHeight = h;
}

void 
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool  
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool 
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void 
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool 
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void 
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int AnimatedSprite::GetFrameWidth() const
{
	return m_frameWidth;
}

int AnimatedSprite::GetFrameHeight() const
{
	return m_frameHeight;
}

int AnimatedSprite::GetXCoord() const
{
	return m_coordContainer.at(m_currentFrame);
}

void AnimatedSprite::SetYCoord(int y)
{
	m_yCoord = y;
}

int AnimatedSprite::GetYCoord() const
{
	return m_yCoord;
}
