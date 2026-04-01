/*
 *  Vector2D.cpp
 *  Defines vector behavior when using certain operators.
 */

#include "Vector2D.h"

#include <cmath>
#include <math.h>

bool Vector2D::operator==(const Vector2D &vector) const {
    return x == vector.x && y == vector.y;
}

bool Vector2D::operator!=(const Vector2D &vector) const {
    return x != vector.x || y != vector.y;
}

Vector2D Vector2D::operator+(Vector2D& vector) const {
    return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator-() const {
    return Vector2D(-x, -y);
}

Vector2D Vector2D::operator-(Vector2D& vector) const {
    return Vector2D(x - vector.x, y - vector.y);
}

// member operator function so we can use the Vector2D that we want to change on the left
Vector2D& Vector2D::operator+=(const Vector2D &vector) {
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &vector) {
    this->x -= vector.x;
    this->y -= vector.y;
    return *this;
}

// member operator function so we can use the Vector2D on the left hand side
Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

// non-member operator function to let us put the 2D vector on the right hand side
Vector2D operator*(float scalar, Vector2D& vector) {
    return Vector2D(vector.x * scalar, vector.y * scalar);
}

Vector2D Vector2D::operator/(float scalar) const {
    return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

Vector2D &Vector2D::normalize() {
    // pythagorean theorem
    float length = sqrt(x * x + y * y);

    // if the length was 4.4
    // x = x/4.4
    if (length > 0) {
        this->x /= length;
        this->y /= length;
    }

    return *this;
}