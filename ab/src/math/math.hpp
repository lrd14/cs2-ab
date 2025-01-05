#pragma once
#include <windows.h>
#include <numbers>
#include <cmath>

struct view_matrix_t 
{
	float* operator()(int index)
	{
		return matrix[index];
	}

	float matrix[4][4];
};

struct Vector
{
public:
	constexpr Vector(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }

	constexpr const Vector& operator-(const Vector& other) const noexcept;
	constexpr const Vector& operator+(const Vector& other) const noexcept;
	constexpr const Vector& operator/(const float factor) const noexcept;
	constexpr const Vector& operator*(const float factor) const noexcept;

	const static bool world_to_screen(view_matrix_t view_matrix, Vector& in, Vector& out);

	float x, y, z;
};
