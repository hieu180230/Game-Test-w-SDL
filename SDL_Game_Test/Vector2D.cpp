#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0;
	y = 0.0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2D& Vector2D::Sub(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::Multp(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D& Vector2D::Div(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vector2D& operator+(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Add(vec2);
}
Vector2D& operator-(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Sub(vec2);
}
Vector2D& operator*(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Multp(vec2);
}
Vector2D& operator/(Vector2D vec1, const Vector2D vec2)
{
	return vec1.Div(vec2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Sub(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multp(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Div(vec);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this -> x *= i;
	this->y *= i;
	return *this;
}
Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

ostream& operator << (ostream& stream, const Vector2D vec)
{
	stream << "[" << vec.x << ":" << vec.y << "]";
	return stream;
}