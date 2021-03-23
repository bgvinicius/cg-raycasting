#include "project/vector3.hpp"
#include <math.h>
#include <iostream>


Vector3::Vector3(float x, float y, float z): from(Point3(0, 0, 0)), to(Point3(x, y, z)) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(Point3 from, Point3 to): from(from), to(to) {
    Vector3 dif = to - from;

    this->x = dif.x;
    this->y = dif.y;
    this->z = dif.z;
}

inline Vector3 Vector3::reverse() { return Vector3(-x, -y, -z); }

inline Vector3 Vector3::operator+=(const Vector3 &v) {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

inline Vector3 Vector3::operator*=(const float factor) {
    return Vector3(x*factor, y*factor, z*factor);
}

inline float Vector3::length() {
    return sqrt(length_squared());
}

inline float Vector3::length_squared() {
    return x*x + y*y + z*z;
}

// inline Vector3 operator+(const Vector3 &u, const Vector3 &v) {
//     return Vector3(u.x + v.x, u.y + v.y, u.z + v.z);
// }

// inline Vector3 operator-(const Vector3 &u, const Vector3 &v) {
//     return Vector3(u.x - v.x, u.y - v.y, u.z - v.z);
// }

// inline Vector3 operator -(Point3 &a, Point3 &b) {
//     return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
// }

// // inline Vector3 operator*(const Vector3 &u, const Vector3 &v) {
// //     return Vector3(u.x * v.x, u.y * v.y, u.z * v.z);
// // }

// inline Vector3 operator*(float t, const Vector3 &v) {
//     return Vector3(t*v.x, t*v.y, t*v.z);
// }

// inline Vector3 operator*(const Vector3 &v, float t) {
//     return t * v;
// }

// inline Vector3 operator/(Vector3 v, float t) {
//     return (1/t) * v;
// }

// inline float dot(const Vector3 &u, const Vector3 &v) {
//     return u.x * v.x
//          + u.y * v.y
//          + u.z * v.z;
// }

// inline Vector3 cross(const Vector3 &u, const Vector3 &v) {
//     return Vector3(u.y * v.z - u.z * v.y,
//                 u.z * v.x - u.x * v.z,
//                 u.x * v.y - u.y * v.x);
// }

// inline Vector3 unit_vector(Vector3 v) {
//     return v / v.length();
// }

std::ostream& operator<<(std::ostream &out, const Vector3 &v) {
    return out << '(' << v.x << ' ' << v.y << ' ' << v.y << ')';
}