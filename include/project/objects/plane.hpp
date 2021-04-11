#include "../object.hpp"

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
};