#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "./component.hpp"

class Material {
    public:
        Component ambient;
        Component diffuse;
        Component specular;
        float shine = 1.0;

        Material(): 
            ambient(Component(0, 0, 0)), 
            diffuse(Component(0, 0, 0)), 
            specular(Component(0, 0, 0)) {}

        Material(Component ambient, Component diffuse, Component specular, float shine):
            ambient(ambient),
            diffuse(diffuse),
            specular(specular) {
                this->shine = shine;
            }
};

#endif