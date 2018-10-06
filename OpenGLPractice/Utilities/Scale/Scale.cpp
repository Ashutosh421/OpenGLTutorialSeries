#include "Scale.h"

Vector2f Scale::size{2048 , 1536};

void Scale::setViewPort(GLuint x , GLuint y , GLuint width , GLuint height) {
	glViewport(x, y, width, height);
	Scale::size.x = width;
	Scale::size.y = height;
}

Vector2f Scale::NormalizedScreenCordinates(Vector2f screenCordinates) {
	Vector2f screenCords{ screenCordinates.x / Scale::size.x , screenCordinates.y / Scale::size.y };
	screenCords.x -= 0.5f;
	screenCords.y -= 0.5f;
	return screenCords;
}

