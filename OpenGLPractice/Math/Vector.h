#pragma once

#include <math.h>

template <class T>
struct Vector
{
public: 
	virtual const T& Add(const T&) = 0;
	virtual const T& Subtract(const T&) = 0;
	virtual float Dot(const T&) = 0;

	virtual float Magnitude() const = 0;
};
