#include "Vec2.h"

namespace Quartz
{
	Vec2::Vec2(float x, float y) noexcept:  x(x), y(y)
	{
	}

	Vec2::Vec2(const Vec2& vec) noexcept : x(vec.x), y(vec.y)
	{
	}

	Vec2 Vec2::operator+(const Vec2& other) const noexcept
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 Vec2::operator-(const Vec2& other) const noexcept
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 Vec2::operator*(const Vec2& other) const noexcept
	{
		return Vec2(x * other.x, y * other.y);
	}

	Vec2 Vec2::operator/(const Vec2& other) const noexcept
	{
		return Vec2(x / other.x, y / other.y);;
	}

	Vec2 Vec2::operator*(float scalar) const noexcept
	{
		return Vec2(x * scalar, y * scalar);
	}

	Vec2 Vec2::operator/(float scalar) const noexcept
	{
		return Vec2(x / scalar, y / scalar);
	}

	Vec2& Vec2::operator+=(const Vec2& other) noexcept
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2& Vec2::operator-=(const Vec2& other) noexcept
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vec2& Vec2::operator*=(const Vec2& other) noexcept
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vec2& Vec2::operator/=(const Vec2& other) noexcept
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vec2& Vec2::operator*=(float scalar) noexcept
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vec2& Vec2::operator/=(float scalar) noexcept
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	Vec2 operator*(float scalar, const Vec2& vec) noexcept
	{
		return vec * scalar;
	}

	Vec2 operator/(float scalar, const Vec2& vec) noexcept
	{
		return vec / scalar;
	}

}