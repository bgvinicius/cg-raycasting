#include "project/vector3.hpp"
#include <math.h>
#include <iostream>


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