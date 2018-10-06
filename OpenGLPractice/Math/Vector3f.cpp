#include "Vector3f.h"

void Vector3f::operator=(const Vector3f& other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

Vector3f Vector3f::operator+(const Vector3f& other) {
	return Vector3f(*this).Add(other);
}

void Vector3f::operator+=(const Vector3f& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

Vector3f Vector3f::operator-(const Vector3f& other) {
	return Vector3f(*this).Subtract(other);
}

void Vector3f::operator-=(const Vector3f& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->x -= other.z;
}

Vector3f Vector3f::operator*(float scalar) {
	Vector3f result{ *this };
	result.x *= scalar;
	result.y *= scalar;
	result.z *= scalar;
	return result;
}

void Vector3f::operator*=(float scalar) {
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
}

Vector3f Vector3f::operator/(float scalar) {
	Vector3f result{ *this };
	result.x /= scalar;
	result.y /= scalar;
	result.z /= scalar;
	return result;
}

void Vector3f::operator/=(float scalar) {
	this->x /= x;
	this->y /= y;
	this->z /= z;
}

const Vector3f& Vector3f::Add(const Vector3f& other) {
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return (*this);
}

const Vector3f& Vector3f::Subtract(const Vector3f& other) {
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return (*this);
}

float Vector3f::Dot(const Vector3f& other) {
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

Vector3f Vector3f::Cross(const Vector3f& other) {
	return Vector3f{(this->y * other.z - this->z * other.y), (this->x * other.z - this->z * other.x), (this->z * other.y - this->y * other.x)};
}

float Vector3f::Magnitude() const{
	return sqrtf(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

/*
	Angle Between two Vector3fs
*/
float Vector3f::Angle(const Vector3f& first, const Vector3f& second) {
	Vector3f temp{ first };
	float dot = temp.Dot(second);
	float magnitude_F = first.Magnitude();
	float magnitude_S = second.Magnitude();
	return acos(dot / magnitude_F * magnitude_S);
}




