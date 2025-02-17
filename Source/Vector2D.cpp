#include "Vector2D.hpp"

Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Vector2D::GetX() const
{
	return x;
}

void Vector2D::SetX(int x)
{
	this->x = x;
}

int Vector2D::GetY() const
{
	return y;
}

void Vector2D::SetY(int y)
{
	this->y = y;
}

