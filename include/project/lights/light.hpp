#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "./component.hpp"
#include "../vector3.hpp"
#include "./material.hpp"

class Light {
    public:
        Component ambient;
        Component diffuse;
        Component specular;

        Light(Component uniform): ambient(Component()), diffuse(uniform), specular(uniform) {
            
        }

        Light(Component diffuse, Component specular): ambient(Component()), diffuse(diffuse), specular(specular) {

        }

        Light(Component ambient, Component specular, Component diffuse): ambient(ambient), diffuse(diffuse), specular(specular) {

        }

        // n: Normal to surface point at ray interception
        // p: Interception point
        // v: Vector from the interception point to the observer
        virtual Component contribution(Vector3 &n, Point3 &p, Vector3 &v, Material &material) = 0;
};

class Ambient: public Light {
    public:
        Ambient(float intensity): Light(Component(intensity, intensity, intensity), Component(), Component()) {

        }

        Ambient(Component ambient): Light(ambient, Component(), Component()) {}

        Component contribution(Vector3 &n, Point3 &p, Vector3 &v, Material &material) {
            return Component(
                ambient.r * material.ambient.r,
                ambient.g * material.ambient.g,
                ambient.b * material.ambient.b
            );
        }
};

class Point: public Light {

};

#endif