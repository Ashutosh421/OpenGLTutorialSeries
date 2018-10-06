#pragma once

#include "Vector.h"

struct Vector3f : public Vector<Vector3f>
{
public:
	float x, y, z;

	Vector3f() :Vector3f(0, 0, 0) {}  //Constructor Delegation
	Vector3f(float x, float y, float z) :x(x), y(y), z(z) {}; //Initializing the variables
	Vector3f(const Vector3f& other) :Vector3f(other.x, other.y, other.z) {};
	void operator=(const Vector3f&);

	virtual const Vector3f& Add(const Vector3f&) override;
	virtual const Vector3f& Subtract(const Vector3f&) override;
	virtual float Dot(const Vector3f&) override;
	Vector3f Cross(const Vector3f&);
	virtual float Magnitude() const override;

	static float Angle(const Vector3f& , const Vector3f&);

	//OverLoad Arithmetic Operators
	Vector3f operator+(const Vector3f&);
	void operator+=(const Vector3f&);

	Vector3f operator-(const Vector3f&);
	void operator-=(const Vector3f&);

	Vector3f operator*(float);
	void operator*=(float);

	Vector3f operator/(float);
	void operator/=(float);
};

