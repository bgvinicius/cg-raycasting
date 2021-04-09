#ifndef OBJECT_H
#define OBJECT_H
#include "ray.hpp"
#include "vector3.hpp"
#include "interception.hpp"

class Object {
    public:
        virtual void intercepts(Ray &ray, InterceptionInfo &info) = 0;
        virtual Vector3 normalAt(Point3 &point) = 0;
};

#endif