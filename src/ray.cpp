#include "project/ray.hpp"

Ray::Ray(Point3 origin, Vector3 direction): origin(origin), direction(direction) {

}

Point3 Ray::pointAt(float t) {
    float x = origin.x + t*direction.x;
    float y = origin.y + t*direction.y;
    float z = origin.z + t*direction.z;

    return Point3(x, y, z);
}