#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();

	int GetX() const;
	void SetX(int x);
	int GetY() const;
	void SetY(int y);

	// TODO: Add magnitude, normalized and different operators, maybe?

private:
	int x;
	int y;
};


//class Vector2D
//{
//public:
//    int x, y;
//
//    Vector2D() : x(0), y(0) {}
//    Vector2D(int x, int y) : x(x), y(y) {}
//
//    // Operator Overloads
//    Vector2D operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
//    Vector2D operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
//    Vector2D operator*(int scalar) const { return Vector2D(x * scalar, y * scalar); }
//    Vector2D operator/(int scalar) const { return (scalar != 0) ? Vector2D(x / scalar, y / scalar) : *this; }
//
//    bool operator==(const Vector2D& v) const { return x == v.x && y == v.y; }
//    bool operator!=(const Vector2D& v) const { return !(*this == v); }
//
//    // Manhattan Distance (for tile-based movement)
//    int ManhattanDistance(const Vector2D& v) const { return abs(x - v.x) + abs(y - v.y); }
//
//    // Clamp values to prevent exceeding a limit
//    void Clamp(int minX, int minY, int maxX, int maxY)
//    {
//        x = std::max(minX, std::min(x, maxX));
//        y = std::max(minY, std::min(y, maxY));
//    }
//};