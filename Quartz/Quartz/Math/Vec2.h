#ifndef QUARTZ_VEC_2_H
#define QUARTZ_VEC_2_H

namespace Quartz
{
	struct Vec2
	{
		float x;
		float y;

		Vec2() = default;

		Vec2(float x, float y) noexcept;

		Vec2(const Vec2& vec) noexcept;

		Vec2 operator+(const Vec2& other) const noexcept;
		Vec2 operator-(const Vec2& other) const noexcept;
		Vec2 operator*(const Vec2& other) const noexcept;
		Vec2 operator/(const Vec2& other) const noexcept;

		Vec2 operator*(float scalar) const noexcept;
		friend Vec2 operator*(float scalar, const Vec2& vec) noexcept;

		Vec2 operator/(float scalar) const noexcept;
		friend Vec2 operator/(float scalar, const Vec2& vec) noexcept;

		Vec2& operator+=(const Vec2& other) noexcept;
		Vec2& operator-=(const Vec2& other) noexcept;
		Vec2& operator*=(const Vec2& other) noexcept;
		Vec2& operator/=(const Vec2& other) noexcept;

		Vec2& operator*=(float scalar) noexcept;
		Vec2& operator/=(float scalar) noexcept;
	};
}

#endif