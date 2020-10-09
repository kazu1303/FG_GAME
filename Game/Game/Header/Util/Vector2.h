#pragma once
#include <math.h>
const float PI = (float)acos(-1);//‰~ü—¦
class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float X ,float Y);
	~Vector2();
	//‰~‚ğ•`‚­‚æ‚¤‚ÉˆÊ’u‚ğ•Ï‚¦‚é
	void AngleToVector(float angle);
	//’PˆÊƒxƒNƒgƒ‹‰»
	void Normalize();
	//ƒ[ƒ‚É
	void Zero();
	void ReSetting(float X, float Y);
	float Length();


	Vector2 operator +(Vector2& value);
    Vector2 operator -(Vector2& value);
	Vector2 operator *(Vector2& value);
	Vector2 operator /(Vector2& value);
	Vector2 operator +=(Vector2& value);
};

inline Vector2::Vector2()
{
}

inline Vector2::Vector2(float X, float Y)
{
	x = X;
	y = Y;
}

inline Vector2::~Vector2()
{}

inline Vector2 Vector2::operator+(Vector2& value)
{
	return Vector2(x += value.x,y += value.y);
}

inline Vector2 Vector2::operator-(Vector2& value)
{
	return Vector2(x -= value.x, y -= value.y);
}

inline Vector2 Vector2::operator*(Vector2& value)
{
	return Vector2(x *= value.x, y *= value.y);
}

inline Vector2 Vector2::operator/(Vector2& value)
{
	return Vector2(x /= value.x, y /= value.y);
}

inline Vector2 Vector2::operator+=(Vector2& value)
{
	return Vector2(x += value.x, y += value.y);
}

//‰~‚ğ•`‚­‚æ‚¤‚ÉˆÊ’u‚ğ•Ï‚¦‚é
inline void Vector2::AngleToVector(float angle)
{
	float thisangle = angle;
	thisangle = thisangle * PI / 180.0f;
	x = (float)sin(thisangle);
	y = (float)cos(thisangle);
}

//’PˆÊƒxƒNƒgƒ‹‰»
inline void Vector2::Normalize()
{
	float length = sqrtf((x * x) + (y * y));
	x /= length;
	y /= length;
	if (length == 0)
	{
		x = 0;
		y = 0;
	}
}

//ƒ[ƒ‚É
inline void Vector2::Zero()
{
	x = 0;
	y = 0;
}

inline void Vector2::ReSetting(float X, float Y)
{
	x = X;
	y = Y;
}

inline float Vector2::Length()
{
	return sqrtf((x * x) + (y * y));
}

 