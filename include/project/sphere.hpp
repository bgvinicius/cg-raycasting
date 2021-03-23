#include "point3.hpp"
#include "ray.hpp"

class Sphere {
    public:
        float radius;
        Point3 center;
        Sphere(Point3 center, float radius);
        float intersectColor(Ray &ray);
};