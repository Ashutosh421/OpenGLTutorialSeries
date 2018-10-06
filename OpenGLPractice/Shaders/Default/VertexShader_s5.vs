#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertColor;

vec3 newPosition;

uniform vec2 horiOffset;

void main(){
	newPosition = position;
	newPosition.x += horiOffset.x;
	newPosition.y += horiOffset.y;
	gl_Position = vec4(newPosition , 1.0);
	vertColor = position;
}