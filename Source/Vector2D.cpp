#include "Vector2D.hpp"
#include "math.h"
#include <algorithm>    // std::max


// Constructors
Vector2D::Vector2D() : x(0), y(0) {}
Vector2D::Vector2D(int x, int y) : x(x), y(y) {}

// Setters & Getters
int Vector2D::GetX() const { return x; }
int Vector2D::GetY() const { return y; }
void Vector2D::SetX(int x) { this->x = x; }
void Vector2D::SetY(int y) { this->y = y; }

// Vector Addition, Substraction, Multiplcation & Division (latter might not work as well as it is int)
Vector2D Vector2D::operator+(const Vector2D& vector) const
{
	return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D& vector) const
{
	return Vector2D(x - vector.x, y - vector.y);
}

Vector2D Vector2D::operator*(int scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(int scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

// Vector comparison 
bool Vector2D::operator==(const Vector2D& vector) const
{
	if (x == vector.x && y == vector.y) return true;
	else return false;
}

bool Vector2D::operator!=(const Vector2D& vector) const
{
	if (x != vector.x || y != vector.y) return true;
	else return false;
}

// Manhattan Distance (for tile-based movement)
int Vector2D::ManhattanDistance(const Vector2D& vector)
{
	return abs(x - vector.x) + abs(y - vector.y);
}

// Clamp values to prevent exceeding a limit
void Vector2D::Clamp(int minX, int minY, int maxX, int maxY)
{
	x = std::max(minX, std::min(x, maxX)); // sets x to max or min depending on if its smaller or greater
	y = std::max(minY, std::min(y, maxY)); // sets y to max or min depending on if its smaller or greater
}

