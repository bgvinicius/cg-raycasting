#include "../object.hpp"
#ifndef PLANE_H
#define PLANE_H

class Plane: public Object {
    public:
        Point3 planePoint;
        Vector3 planeNormal;

        Plane(Point3 planePoint, Vector3 planeNormal, Material material): 
            Object(material), planePoint(planePoint), planeNormal(unit_vector(planeNormal)) {

        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
            float numer = dot((planePoint - ray.origin), planeNormal);
            float den = dot(ray.direction, planeNormal);

            if (den == 0 || (numer / den) <= 1) {
                return;
            }

            info.updateInterception(numer / den, this);
        }

        Vector3 normalAt(Point3 &point) {
            return planeNormal;
        };

        void toCamera(Matrix4 &toCamera) {
            this->planePoint = this->planePoint * toCamera;
            this->planeNormal = unit_vector(this->planeNormal * toCamera);
        }
};

class CircularPlane: public Object {
    public:
        Point3 planeCenter;
        Vector3 planeNormal;
        float radius;

        CircularPlane(Point3 planeCenter, Vector3 planeNormal, float radius, Material material): 
            Object(material), planeCenter(planeCenter), planeNormal(unit_vector(planeNormal)) {
            this-> radius = radius;
        }

        CircularPlane(): planeCenter(Point3(0, 0, 0)), planeNormal(Vector3(0, 0, 0)) {

        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
            float numer = dot((planeCenter - ray.origin), planeNormal);
            float den = dot(ray.direction, planeNormal);

            if (den == 0 || (numer / den) <= 1) {
                return;
            }
            
            float t = numer / den;
            
            Point3 hitPoint = ray.pointAt(t);
            Vector3 centerToHitPoint = hitPoint - planeCenter;

            if (centerToHitPoint.length() > radius) {
                return;
            } 

            info.updateInterception(t, this);
        }

        Vector3 normalAt(Point3 &point) {
            return planeNormal;
        };
};

#endif