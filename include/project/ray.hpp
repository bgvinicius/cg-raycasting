#include "point3.hpp"
#include "vector3.hpp"

class Ray {
    public:
        Point3 origin;
        Vector3 direction;

        Ray(Point3 origin, Vector3 direction);
        Point3 pointAt(float t);
};
