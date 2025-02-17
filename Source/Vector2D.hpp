#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();

	// Setters & Getters
	int GetX() const;
	int GetY() const;
	void SetX(int x);
	void SetY(int y);

	// Vector Addition, Substraction, Multiplcation & Division (latter might not work as well as it is int)
	Vector2D operator+(const Vector2D& vector) const;
	Vector2D operator-(const Vector2D& vector) const;
	Vector2D operator*(int scalar) const;
	Vector2D operator/(int scalar) const;

	// Vector comparison 
	bool operator==(const Vector2D& vector) const;
	bool operator!=(const Vector2D& vector) const;

	// Manhattan Distance (for tile-based movement)
	int ManhattanDistance(const Vector2D& vector);

	// Clamp values to prevent exceeding a limit
	void Clamp(int minX, int minY, int maxX, int maxY);

private:
	int x;
	int y;
};