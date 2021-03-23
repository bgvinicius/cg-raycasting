#include "project/sphere.hpp"
#include "project/vector3.hpp"
#include <math.h>

Sphere::Sphere(Point3 center, float radius): center(center) {
    this->radius = radius;
}

float Sphere::intersectColor(Ray &ray) {
    Vector3 oc = ray.origin - center;//  r.origin() - center;

    auto a = dot(ray.direction, ray.direction);
    auto b = 2.0 * dot(oc, ray.direction);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}
