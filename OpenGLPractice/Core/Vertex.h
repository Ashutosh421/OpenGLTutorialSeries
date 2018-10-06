#pragma once

#include "../../Math/Vector3f.h"

struct Vertex
{
public:
	Vector3f position;
	Vector3f color;

	Vertex():Vertex(Vector3f{ 0, 0 , 0 }, Vector3f{ 0 , 0 ,0 }) {}
	Vertex(Vector3f position, Vector3f color) :position(position), color(color) {}
	Vertex(const Vertex& other) :Vertex(other.position, other.color) {}
	void operator=(const Vertex& other) {
		this->position = other.position;
		this->color = other.color;
	}

	~Vertex(){}
};

