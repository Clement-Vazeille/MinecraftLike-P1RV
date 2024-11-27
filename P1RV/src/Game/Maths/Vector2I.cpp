#include "Vector2I.h"

Vector2I::Vector2I() : Vector2I(0,0)
{
}

Vector2I::Vector2I(int xPosition, int zPosition) : 
	x(xPosition),z(zPosition)
{
}

void Vector2I::setX(int xi)
{
	x = xi;
}

void Vector2I::setZ(int zi)
{
	z = zi;
}

int Vector2I::getX(void) const
{
	return x;
}

int Vector2I::getZ(void) const
{
	return z;
}

void Vector2I::operator+=(const Vector2I& param)
{
	x += param.getX();
	z += param.getZ();
}

Vector2I Vector2I::operator+(const Vector2I& param) const
{
	return Vector2I(x+param.getX(),z+param.getZ());
}

Vector2I Vector2I::operator-(const Vector2I& param) const
{
	return Vector2I(x - param.getX(), z - param.getZ());
}

Vector2I Vector2I::operator*(const int& coeff) const
{
	return Vector2I(x*coeff,z*coeff);
}

bool Vector2I::operator==(const Vector2I& param) const
{
	return (x == param.getX() && z == param.getZ());
}