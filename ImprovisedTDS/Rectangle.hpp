#pragma once
#include <string>
#include "Vector2.hpp"

struct Rectangle
{
	float X = 0;
	float Y = 0;
	float Width = 0;
	float Height = 0;

	Rectangle() { }
	Rectangle(float x, float y, float width, float height)
		: X(x), Y(y), Width(width), Height(height)
	{ }
	Rectangle(Vector2<float> location, Vector2<float> size)
		: X(location.X), Y(location.Y),
		Width(size.X), Height(size.Y)
	{ }

	float Left() const
	{
		return X;
	}
	float Right() const
	{
		return X + Width;
	}
	float Top() const
	{
		return Y;
	}
	float Bottom() const
	{
		return Y + Height;
	}

	bool IsEmpty() const
	{
		return ((((Width == 0) && (Height == 0)) && (X == 0)) && (Y == 0));
	}

	Vector2f Location() const
	{
		return Vector2f(X, Y);
	}

	Vector2f Size() const
	{
		return Vector2f(Width, Height);
	}

	bool Intersects(const Rectangle& value) const
	{
		return
			value.Left() < Right() &&
			Left() < value.Right() &&
			value.Top() < Bottom() &&
			Top() < value.Bottom();
	}

	static bool Intersects(const Rectangle& a, const Rectangle& b)
	{
		return a.Intersects(b);
	}

	std::string ToString() const
	{
		return "{" + std::to_string(X) + "," + std::to_string(Y) +
			" | " + std::to_string(Width) + "," + std::to_string(Height) + "}";
	}

	bool operator==(const Rectangle& a) const
	{
		return ((a.X == X) && (a.Y == Y) && (a.Width == Width) && (a.Height == Height));
	}
	bool operator!=(const Rectangle& a) const
	{
		return !(*this == a);
	}
};
