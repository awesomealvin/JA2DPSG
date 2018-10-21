#pragma once
#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	float GetX() const;
	float GetY() const;

	void SetX(float x);
	void SetY(float y);

	void Set(float x, float y);

	float m_x;
	float m_y;

private:
	
};

#endif

