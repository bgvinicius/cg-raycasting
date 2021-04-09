#include "../point3.hpp"
#include "../ray.hpp"
#include "../object.hpp"

class Sphere: public Object {
    public:
        float radius;
        Point3 center;
        Sphere(Point3 center, float radius): center(center) {
            this->radius = radius;
        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
            Vector3 oc = ray.origin - center;//  r.origin() - center;

            auto a = dot(ray.direction, ray.direction);
            auto b = 2.0 * dot(oc, ray.direction);
            auto c = dot(oc, oc) - radius*radius;
            auto discriminant = b*b - 4*a*c;
            
            if (discriminant < 0) {
                return;
            }

            float t1 = (-b + sqrt(discriminant)) / (2*a);
            float t2 = (-b - sqrt(discriminant)) / (2*a);

            // if(discriminant >= 0) {
            //     std::cerr << "t1 " << t1 << " t2 " << t2 << "\n";
            //     auto p = ray.pointAt(t1);
            //     std::cerr << "x: " << p.x << " y: " << p.y << " z: " << p.z << "\n";
            // }

            info.updateInterception(t2, this);
        }

        Vector3 normalAt(Point3 &point) {
            return unit_vector(point - center);
        };
};