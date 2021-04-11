
#ifndef INTERCEPTIONINFO_H
#define INTERCEPTIONINFO_H
#include "ray.hpp"
#include "lights/light.hpp"
#include <vector>

using namespace std;

class Object;
class InterceptionInfo {
    public:
        float currentT = 100000.0;
        bool valid = false;
        Object *hitObject;
        Ray ray;

        InterceptionInfo(Ray &ray): ray(ray) {}

        void updateInterception(float newHit, Object* newObject) {
            if (newHit < currentT) {
                           // std::cerr << "a";

                currentT = newHit;
                hitObject = newObject;
                valid = true;
            }
        }

        Point3 getHitPoint() {
            return ray.pointAt(currentT);
        }
};

#endif