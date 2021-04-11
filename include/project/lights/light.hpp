#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "./component.hpp"
#include "../vector3.hpp"
#include "./material.hpp"
#include <vector>
using namespace std;
#include <assert.h>

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

// for non-ambient lights. Takes the components of the light + direction vector + default info for any light (normal, hit to observer vector)
Component genericLightContribution(Vector3 &normal, Vector3 &hitToObserver, Vector3 &hitToLight, 
                                   Light &light, Material &material) {
    Component currentContribution = Component();

    // check if vectors are normalized.
    assert(normal.length() == 1);
    assert(hitToObserver.length() == 1);
    assert(hitToLight.length() == 1);
    
    float n_dot_l = dot(normal, hitToLight);

    if (n_dot_l > 0) {
        // i += 0.5 * (n_dot_l / (normal.length() * lightD.length()));
        currentContribution.r += material.diffuse.r * light.diffuse.r * n_dot_l;
        currentContribution.g += material.diffuse.g * light.diffuse.g * n_dot_l;
        currentContribution.b += material.diffuse.b * light.diffuse.b * n_dot_l;
    }

    Vector3 R = ((2 * dot(hitToLight, normal)) * normal) - hitToLight; // ((2.0 * normal) * dot(normal, lightD)) - lightD;
    float rdotv = dot(R, hitToObserver);

    if (rdotv > 0) {
        float rdtov_raised_m = pow(rdotv, material.shine);

        currentContribution.r += material.specular.r * light.specular.r * rdtov_raised_m;
        currentContribution.g += material.specular.g * light.specular.g * rdtov_raised_m;
        currentContribution.b += material.specular.b * light.specular.b * rdtov_raised_m;
    }

    return currentContribution;
}

class AmbientLight: public Light {
    public:
        AmbientLight(float intensity): Light(Component(intensity, intensity, intensity), Component(), Component()) {

        }

        AmbientLight(Component ambient): Light(ambient, Component(), Component()) {}

        Component contribution(Vector3 &n, Point3 &p, Vector3 &v, Material &material) {
            return Component(
                ambient.r * material.ambient.r,
                ambient.g * material.ambient.g,
                ambient.b * material.ambient.b
            );
        }
};

class PointLight: public Light {
    public:
        Point3 position;
        PointLight(Point3 position, Component diffuse, Component specular): Light(diffuse, specular), position(position) {}

        Component contribution(Vector3 &n, Point3 &p, Vector3 &v, Material &material) {
            Vector3 hitToLight = unit_vector(position - p);

            return genericLightContribution(n, v, hitToLight, *this, material);
        }
};

#endif