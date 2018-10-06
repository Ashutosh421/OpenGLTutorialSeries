#include "Vector2f.h"


void Vector2f::operator=(const Vector2f& other) {
	this->x = other.x;
	this->y = other.y;
}

Vector2f Vector2f::operator+(const Vector2f& other) {
	return Vector2f(*this).Add(other);
}
void Vector2f::operator+=(const Vector2f& other) {
	this->x += other.x;
	this->y += other.y;
}

Vector2f Vector2f::operator-(const Vector2f& other) {
	return Vector2f(*this).Subtract(other);
}
void Vector2f::operator-=(const Vector2f& other) {
	this->x -= other.x;
	this->y -= other.y;
}

Vector2f Vector2f::operator*(float scalar) {
	Vector2f result{ *this };
	result.x *= scalar;
	result.y *= scalar;
	return result;
}
void Vector2f::operator*=(float scalar) {
	this->x *= scalar;
	this->y *= scalar;
}

Vector2f Vector2f::operator/(float scalar) {
	Vector2f result{ *this };
	result.x /= scalar;
	result.y /= scalar;
	return result;
}
void Vector2f::operator/=(float scalar) {
	this->x /= scalar;
	this->y /= scalar;
}

const Vector2f& Vector2f::Add(const Vector2f& other) {
	this->x += other.x;
	this->y += other.y;
	return (*this);
}

const Vector2f& Vector2f::Subtract(const Vector2f& other) {
	this->x -= other.x;
	this->y -= other.y;
	return (*this);
}

float Vector2f::Dot(const Vector2f& other) {
	return 0.0f;
}

float Vector2f::Magnitude() const {
	return sqrtf(pow(this->x, 2) + pow(this->y, 2));
}

float Vector2f::Angle(const Vector2f& first, const Vector2f& second) {
	return atan2f(second.y - first.y , second.x - first.x);
}

