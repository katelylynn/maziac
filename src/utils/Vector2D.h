/*
 *  Vector2D.h
 *  Defines all possible operations that can be done on a vector.
 */

#ifndef MAZIAC_VECTOR2D_H
#define MAZIAC_VECTOR2D_H

class Vector2D {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2D(float x, float y) : x(x), y(y) {}

    bool operator==(const Vector2D& vector) const;

    bool approxEquals(const Vector2D& vector, float tolerance) const;

    bool operator!=(const Vector2D& vector) const;

    Vector2D operator+(Vector2D& vector) const;

    Vector2D operator-() const;

    Vector2D operator-(Vector2D& vector) const;

    // member operator function
    // using & bc we want it to return itself, instead of creating a new Vector2D
    // vector we want to return on the left side of the operation, vector we want to add on the right
    Vector2D& operator+=(const Vector2D& vector);

    Vector2D& operator-=(const Vector2D& vector);

    // member operator function
    // Vector2D on the left, float on the right
    // creates a new Vector2D
    Vector2D operator*(float scalar) const;

    // float on the left, Vector2D on the right
    // friend makes this a nonmember function, which removes the issue of duplicate operator* functions
    friend Vector2D operator*(float scalar, Vector2D& vector);

    Vector2D operator/(float scalar) const;

    Vector2D& operator*=(float scalar);

    Vector2D& operator/=(float scalar);

    Vector2D& normalize();
};

#endif //MAZIAC_VECTOR2D_H