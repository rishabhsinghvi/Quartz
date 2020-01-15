#include "Vec2.h"
#include "Logger/Logger.h"

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
		LOG_ASSERT(scalar != 0.0f, "Vec2: Div by 0 scalar")
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
		LOG_ASSERT(other.x != 0.0f, "Vec2: Div by 0")
		LOG_ASSERT(other.y != 0.0f, "Vec2: Div by 0")
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
		LOG_ASSERT(scalar != 0.0f, "Vec2: Div by 0 scalar")

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