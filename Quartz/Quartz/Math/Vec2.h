#ifndef QUARTZ_VEC_2_H
#define QUARTZ_VEC_2_H

namespace Quartz
{
	struct Vec2
	{
		float x;
		float y;

		Vec2() = default;

		Vec2(float x, float y);

		Vec2(const Vec2& vec);

		Vec2 operator+(const Vec2& other) const;
		Vec2 operator-(const Vec2& other) const;
		Vec2 operator*(const Vec2& other) const;
		Vec2 operator/(const Vec2& other) const;

		Vec2 operator*(float scalar) const;
		friend Vec2 operator*(float scalar, const Vec2& vec);

		Vec2 operator/(float scalar) const;
		friend Vec2 operator/(float scalar, const Vec2& vec);

		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator/=(const Vec2& other);

		Vec2& operator*=(float scalar);
		Vec2& operator/=(float scalar);
	};
}

#endif