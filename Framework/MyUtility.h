#ifndef __MYUTILITY_H__
#define __MYUTILITY_H__

#include "Box2D/Box2D.h"
#include "Vector2.h"

class MyUtility
{
public:
	MyUtility();
	~MyUtility();

	static MyUtility& GetInstance();
	static void DestroyInstance();

	static int RandomInt(int min, int max);

	static float RandomFloat(float min, float max);

	static float ToRadians(float degrees);

	static float ToAngle(float radians);
	 
	static Vector2 CalculateVectorFromAngle(int angle);
	static Vector2 GetDirection(Vector2 start, Vector2 end);
	static b2Vec2 GetDirection(b2Vec2 start, b2Vec2 end);

	static float GetMagnitude(Vector2 v);
	static float GetMagnitude(b2Vec2 v);

	static b2Vec2 ClampMagnitude(b2Vec2 vector, float maxLength);
	 
	static float Clamp(float a, float lower, float upper);
	 
	static float GetRadiansFromVectors(b2Vec2 a, b2Vec2 b);
	 
	static float Lerp(float start, float end, float difference);
	static b2Vec2 Lerp(b2Vec2 start, b2Vec2 end, float difference);
	 
	static const float PI;

private:

	static MyUtility* sm_pInstance;


};

#endif // __MYUTILITY_H__
