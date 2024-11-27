#include "Vector3I.h"

Vector3I::Vector3I() : Vector3I(0,0,0)
{
}

Vector3I::Vector3I(int xi, int yi, int zi) :
    x(xi),y(yi),z(zi)
{
}

void Vector3I::setX(int xi)
{
    x = xi;
}

void Vector3I::setY(int yi)
{
    y = yi;
}

void Vector3I::setZ(int zi)
{
    z = zi;
}

int Vector3I::getX(void) const
{
    return x;
}

int Vector3I::getY(void) const
{
    return y;
}

int Vector3I::getZ(void) const
{
    return z;
}

void Vector3I::operator+=(const Vector3I& param)
{
    x += param.getX();
    y += param.getY();
    z += param.getZ();
}

Vector3I Vector3I::operator+(const Vector3I& param) const
{
    Vector3I res;
    res += (*this);
    res += param;
    return res;
}

Vector3I Vector3I::operator-(const Vector3I& param) const
{
    Vector3I res;
    res += (*this);
    res += (param*(-1));
    return res;
}

Vector3I Vector3I::operator*(const int& coeff) const
{
    return Vector3I(x*coeff,y*coeff,z*coeff);
}

bool Vector3I::operator==(const Vector3I& param) const
{
    return false;
}
