#include "project/sphere.hpp"
#include "project/vector3.hpp"
#include <math.h>
#include <iostream>

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
    }

    auto t1 = (-b + sqrt(discriminant)) / (2*a);
    auto t2 = (-b - sqrt(discriminant)) / (2*a);

    // if(discriminant >= 0) {
    //     std::cerr << "t1 " << t1 << " t2 " << t2 << "\n";
    //     auto p = ray.pointAt(t1);
    //     std::cerr << "x: " << p.x << " y: " << p.y << " z: " << p.z << "\n";
    // }

    return t2;
}
