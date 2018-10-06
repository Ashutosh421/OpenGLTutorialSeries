#pragma once

#include<functional>
#include<iostream>

class Matrix4f
{
public:
	unsigned short cols = 4;
	unsigned short rows = 4;
	float elements[4][4];

	Matrix4f& Add(float);
	Matrix4f& Subtract(float);
	Matrix4f& Multiply(float);
	Matrix4f& Divide(float);

	void Add(const Matrix4f&);
	void Subtract(const Matrix4f&);
	void Multiply(const Matrix4f&);

	static Matrix4f Identity();
	void ForEachElement(std::function<void(float&)>);
	void ForEachElement(const Matrix4f& , std::function<void(float& src, float target)>);
	void ForEachIndex(std::function<void(unsigned short, unsigned short, float&)>);

	friend std::ostream& operator<<(std::ostream&, const Matrix4f&);

	//void operator=(const Matrix4f&);
	Matrix4f();
	~Matrix4f();
};

