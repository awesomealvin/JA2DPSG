#include "Vector2.h"



Vector2::Vector2() :
	m_x(0.0f),
	m_y(0.0f)
{
}

Vector2::Vector2(float x, float y)
{
	m_x = x;
	m_y = y;
}


Vector2::~Vector2()
{
}

float Vector2::GetX() const
{
	return m_x;
}

float Vector2::GetY() const
{
	return m_y;
}

void Vector2::SetX(float x)
{
	m_x = x;
}

void Vector2::SetY(float y)
{
	m_y = y;
}

void Vector2::Set(float x, float y)
{
	m_x = x;
	m_y = y;
}
