#pragma once

#include "Vector.h"

struct Vector2f : public Vector<Vector2f>
{
public:
	float x, y;

	Vector2f() :Vector2f(0, 0) {}  //Constructor Delegation
	Vector2f(float x, float y) :x(x), y(y) {}; //Initializing the variables
	Vector2f(const Vector2f& other) :Vector2f(other.x, other.y) {};
	void operator=(const Vector2f&);

	virtual const Vector2f& Add(const Vector2f&) override;
	virtual const Vector2f& Subtract(const Vector2f&) override;
	virtual float Dot(const Vector2f&) override;
	virtual float Magnitude() const override;

	static float Angle(const Vector2f&, const Vector2f&);

	//OverLoad Arithmetic Operators
	Vector2f operator+(const Vector2f&);
	void operator+=(const Vector2f&);

	Vector2f operator-(const Vector2f&);
	void operator-=(const Vector2f&);

	Vector2f operator*(float);
	void operator*=(float);

	Vector2f operator/(float);
	void operator/=(float);
};



