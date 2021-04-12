#ifndef OBJECT_H
#define OBJECT_H
#include "ray.hpp"
#include "vector3.hpp"
#include "interception.hpp"
#include "./lights/material.hpp"
#include <stdexcept>
#include "./matrix4.hpp"

class Object {
    public:
        Material material;

        Object() {
            
        }

        Object(Material material): material(material) {

        }

        virtual void intercepts(Ray &ray, InterceptionInfo &info) {
            throw std::invalid_argument(
                "We can't intercept an abstract object like this one."
            );        
        }

        virtual Vector3 normalAt(Point3 &point) {
            throw std::invalid_argument(
                "Abstract objects don't have a normal."
            );   
        }

        virtual void toCamera(Matrix4 &toCamera) {
            throw std::invalid_argument(
                "Abstract objects can't be transformed to camera coordinates."
            ); 
        }
};

#endif