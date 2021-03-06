#include "../object.hpp"
#include "../transform.hpp"
#include "./plane.hpp"

class Cylinder: public Object {
    public:
        float baseRadius;
        float height;
        Point3 base;
        Vector3 direction;
        CircularPlane basePlane;
        CircularPlane topPlane;

        Cylinder(Point3 base, float baseRadius, float height, Vector3 direction, Material material):
            Object(material), base(base), direction(unit_vector(direction)) {
            this->baseRadius = baseRadius;
            this->height = height;
            computePlanes();
        }

        void computePlanes() {
            this->basePlane = CircularPlane(this->base, direction.reverse(), baseRadius, this->material);

            Vector3 top = Vector3(base.x, base.y, base.z) + (direction * height);
            this->topPlane = CircularPlane(Point3(top.x, top.y, top.z), direction, baseRadius, this->material);
        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
            basePlane.intercepts(ray, info);
            topPlane.intercepts(ray, info);

            // cylinder base point
            Point3 B = base;

            // cylinder direction vector -- unit vector
            Vector3 u = unit_vector(direction);

            // cylinder height and radius
            float H = height;
            float R = baseRadius;

            // == auxiliary vectors to simplify the interception equation ==
            
            // ray direction
            Vector3 d = ray.direction;

            // ray origin
            Point3 P_0 = ray.origin;

            // v = (P0 - B) - ((P0 - B) dot u) * u
            Vector3 v = (P_0 - B) - ((dot(P_0 - B, u) * u)); 

            // w = d - (d dot u)*u
            Vector3 w = d - ((dot(d, u)) * u);

            // == quadratic equation ==

            float a = dot(w, w);
            float b = dot(v, w);
            float c = dot(v, v) - pow(R, 2);

            float discriminant = pow(b, 2) - (a*c);

            if (discriminant < 0) return;

            float t1 = (-b + sqrt(discriminant)) / a;
            float t2 = (-b - sqrt(discriminant)) / a;

            Point3 p1 = ray.pointAt(t1);
            Point3 p2 = ray.pointAt(t2);

            float h1 = dot(p1 - B, u);
            float h2 = dot(p2 - B, u);

            if (h1 >= 0 and h1 <= H) {
                info.updateInterception(t1, this);
                //return;
            }

            
            if (h2 >= 0 and h2 <= H) {
                info.updateInterception(t2, this);
                //return;
            }

            return;
        }

        Vector3 normalAt(Point3 &point) {
            Vector3 w = point - base;
            Vector3 N = w - (dot(w, direction) * direction);

            return N / baseRadius;
        };

        void toCamera(Matrix4 &toCamera) {
            this->base = this->base * toCamera;
            this->direction = unit_vector(this->direction * toCamera);
            computePlanes();
        }

        void uniformScale(Vector3 &scale, Point3 &ancor) {
            float factor = scale.x;

            this->baseRadius *= factor;
            this->height *= factor;

            this->base = scalePoint(scale, this->base, ancor);
            computePlanes();
        }

        void rotate(Vector3 &axis, float teta) {
            this->base = rotationPoint(axis, this->base, teta);
            computePlanes();

        }

        void translate(Vector3 &dir) {
            this->base = translatePoint(dir, this->base);
            computePlanes();
        }
};