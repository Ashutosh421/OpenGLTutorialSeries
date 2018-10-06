#include "Matrix4f.h"



Matrix4f::Matrix4f()
{	
	this->ForEachElement([&](float &element)->void { element = 0; });
}

Matrix4f& Matrix4f::Add(float scalar) {
	this->ForEachElement([&](float &element)->void { element += scalar; });
	return *this;
}

void Matrix4f::Add(const Matrix4f& other) {
	this->ForEachElement(other, [&](float& src, float target)->void { src += target; });
}

void Matrix4f::Subtract(const Matrix4f& other) {
	this->ForEachElement(other, [&](float& src, float target)->void { src -= target; });
}

Matrix4f Matrix4f::Identity() {
	Matrix4f mat;
	mat.ForEachIndex([](unsigned short r, unsigned short c, float& element)->void {
		if (r == c) {
			element = 1;
		}
	});
	return mat;
}

void Matrix4f::Multiply(const Matrix4f& other) {
	for (unsigned int i = 0; i < this->rows; i++) {
		for (unsigned int j = 0; j < this->cols; j++) {

		}
	}
}

Matrix4f& Matrix4f::Subtract(float scalar) {
	this->ForEachElement([&](float &element)->void { element -= scalar;	});
	return *this;
}

Matrix4f& Matrix4f::Multiply(float scalar) {
	this->ForEachElement([&](float &element)->void { element *= scalar; });
	return *this;
}

Matrix4f& Matrix4f::Divide(float scalar) {
	this->ForEachElement([&](float &element)->void { element /= scalar;	});
	return *this;
}

void Matrix4f::ForEachElement(std::function<void(float&)> lambda) {
	for (unsigned short i = 0; i < this->rows; i++) {
		for (unsigned short j = 0; j < this->cols; j++) {
			lambda(this->elements[i][j]);
		}
	}
}

void Matrix4f::ForEachElement(const Matrix4f& other , std::function<void(float&, float)> lambda) {
	for (unsigned short i = 0; i < this->rows; i++) {
		for (unsigned short j = 0; j < this->cols; j++) {
			lambda(this->elements[i][j], other.elements[i][j]);
		}
	}
}

void Matrix4f::ForEachIndex(std::function<void(unsigned short r, unsigned short c, float& element)> lambda) {
	for (unsigned short i = 0; i < this->rows; i++) {
		for (unsigned short j = 0; j < this->cols; j++) {
			lambda(i , j , this->elements[i][j]);
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Matrix4f& mat) {
	for (unsigned short r = 0; r < mat.rows; r++ ) {
		for (unsigned short c = 0; c < mat.cols; c++) {
			out << mat.elements[r][c] << " ";
		}
		out << std::endl;
	}
	return out;
}


Matrix4f::~Matrix4f()
{

}
