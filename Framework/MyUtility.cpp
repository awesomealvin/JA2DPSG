#include "MyUtility.h"

#include <cstdlib>
#include "logmanager.h"
#include <string>

MyUtility* MyUtility::sm_pInstance = 0;

const float MyUtility::PI = 3.1415926535897f;

MyUtility::MyUtility()
{

}


MyUtility::~MyUtility()
{

}

MyUtility & MyUtility::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new MyUtility();
	}

	return (*sm_pInstance);
}

void MyUtility::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

int MyUtility::RandomInt(int min, int max)
{
	int randomNumber = rand() % (max - min + 1) + min;
	return randomNumber;
}

float MyUtility::RandomFloat(float min, float max)
{
	float random = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
	float range = max - min;

	float randomNumber = (random * range) + min;

	return randomNumber;
}

float MyUtility::ToRadians(float degrees)
{
	return ((degrees * PI) / 180.0f);
}

float MyUtility::ToAngle(float radians)
{
	return (radians * 180.0f) / PI;
}

Vector2 MyUtility::CalculateVectorFromAngle(int angle)
{
	Vector2 output;
	float radians = MyUtility::ToRadians(static_cast<float>(angle));
	float x = cos(radians);
	float y = sin(radians);

	output.SetX(x);
	output.SetY(y);

	return output;
}

Vector2 MyUtility::GetDirection(Vector2 start, Vector2 end)
{
	Vector2 result;

	result.m_x = end.m_x - start.m_x;
	result.m_y = end.m_y - start.m_y;

	return result;
}

b2Vec2 MyUtility::GetDirection(b2Vec2 start, b2Vec2 end)
{
	b2Vec2 result;
	result.x = end.x - start.x;
	result.y = end.y - start.y;
	
	return result;
}

float MyUtility::GetMagnitude(Vector2 v)
{
	
	return static_cast<float>(abs(sqrt((v.m_x * v.m_x) + (v.m_y * v.m_y))));
}

float MyUtility::GetMagnitude(b2Vec2 v)
{
	return static_cast<float>(abs(sqrt((v.x * v.x) + (v.y * v.y))));
}

b2Vec2 MyUtility::ClampMagnitude(b2Vec2 vector, float maxLength)
{
	float c = (vector.x * vector.x) + (vector.y * vector.y); // a^2 + b^2 = c^2;
	float hyp = sqrt(c);

	//std::string debug = "hyp: " + std::to_string(hyp);
	//LogManager::GetInstance().Log(debug.c_str());

	float radius = Clamp(hyp, 0, maxLength);

	float radians = atan2(vector.x, vector.y);

	b2Vec2 newVector;
	newVector.x = sin(radians) * radius;
	newVector.y = cos(radians) * radius;

	return newVector;

}

// My own CLAMP function
float MyUtility::Clamp(float a, float lower, float upper)
{
	return std::max(lower, std::min(a, upper));
}

float MyUtility::GetRadiansFromVectors(b2Vec2 a, b2Vec2 b)
{
	b2Vec2 direction = GetDirection(a, b);
	return atan2(direction.y, direction.x);
}

float MyUtility::Lerp(float start, float end, float difference)
{
	return ((end - start) * difference) + start;
}

b2Vec2 MyUtility::Lerp(b2Vec2 start, b2Vec2 end, float difference)
{
	b2Vec2 returnValue;
	returnValue.x = Lerp(start.x, end.x, difference);
	returnValue.y = Lerp(start.y, end.y, difference);

	return returnValue;
}
