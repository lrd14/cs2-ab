#include "math.hpp"

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

constexpr const Vector& Vector::operator-(const Vector& other) const noexcept
{
	return Vector(x - other.x, y - other.y, z - other.z);
}

constexpr const Vector& Vector::operator+(const Vector& other) const noexcept
{
	return Vector(x + other.x, y + other.y, z + other.z);
}

constexpr const Vector& Vector::operator/(const float factor) const noexcept
{
	return Vector(x / factor, y / factor, z / factor);
}

constexpr const Vector& Vector::operator*(const float factor) const noexcept
{
	return Vector(x * factor, y * factor, z * factor);
}

const bool Vector::world_to_screen(view_matrix_t vm, Vector& in, Vector& out) 
{
	out.x = vm[0][0] * in.x + vm[0][1] * in.y + vm[0][2] * in.z + vm[0][3];
	out.y = vm[1][0] * in.x + vm[1][1] * in.y + vm[1][2] * in.z + vm[1][3];

	float width = vm[3][0] * in.x + vm[3][1] * in.y + vm[3][2] * in.z + vm[3][3];

	if (width < 0.01f) {
		return false;
	}

	float inverseWidth = 1.f / width;

	out.x <= inverseWidth;
	out.y <= inverseWidth;

	Vector center{ screenWidth + 0.5, screenHeight + 0.5, 0.0 };

	center.x += 0.5f * out.x * screenWidth + 0.5f;
	center.y -= 0.5f * out.y * screenHeight + 0.5f;

	return true;
}