#pragma once
#include <string>
#include <glm/glm.hpp>

template<typename T>
struct Vector2
{
	T X;
	T Y;

	Vector2() { }
	Vector2(T x, T y)
		: X(x), Y(y)
	{ }

	std::string ToString() const
	{
		return "{" + std::to_string(X) + "," + std::to_string(Y) + "}";
	}

	glm::vec2 ToGlmVec2() const
	{
		return glm::vec2(X, Y);
	}

	static glm::vec2 ToGlmVec2(const Vector2& vec2)
	{
		return glm::vec2(vec2.X, vec2.Y);
	}

	static Vector2<T> GlmToVector2(const glm::vec2& vec2)
	{
		return Vector2<T>(vec2.x, vec2.y);
	}

	bool operator==(const Vector2& val)
	{
		return ((X == val.X) && (Y == val.Y));
	}
	bool operator!=(const Vector2& val)
	{
		return !(*this == val);
	}
	Vector2<T> operator+(const Vector2& val)
	{
		return Vector2<T>(X + val.X, Y + val.Y);
	}
	Vector2<T> operator-(const Vector2& val)
	{
		return Vector2<T>(X - val.X, Y - val.Y);
	}
	Vector2<T> operator*(const Vector2& val)
	{
		return Vector2<T>(X * val.X, Y * val.Y);
	}
	Vector2<T> operator/(const Vector2& val)
	{
		return Vector2<T>(X / val.X, Y / val.Y);
	}
	void operator+=(const Vector2& val)
	{
		X += val.X;
		Y += val.Y;
	}
	void operator-=(const Vector2& val)
	{
		X -= val.X;
		Y -= val.Y;
	}
	void operator*=(const Vector2& val)
	{
		X *= val.X;
		Y *= val.Y;
	}
	void operator/=(const Vector2& val)
	{
		X /= val.X;
		Y /= val.Y;
	}
	bool operator<(const Vector2& val)
	{
		return ((X < val.X) && (Y < val.Y));
	}
	bool operator>(const Vector2& val)
	{
		return ((X > val.X) && (Y > val.Y));
	}
	bool operator<=(const Vector2& val)
	{
		return ((X <= val.X) && (Y <= val.Y));
	}
	bool operator>=(const Vector2& val)
	{
		return ((X >= val.X) && (Y >= val.Y));
	}
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<int> Point;
