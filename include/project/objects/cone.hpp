#include "../object.hpp"

class Cone: public Object {
    public:
        // your constructor
        Point3 top;
        Vector3 direction;
        float height;
        float baseRadius;

        Cone(Point3 top, Vector3 direction, float height, float baseRadius): top(top), direction(direction) {
            this->height = height;
            this->baseRadius = baseRadius;
        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
            // cone center point
            Point3 C = Point3(0, 0, -3.0);
            // cone top point
            Point3 V = top; Point3(0, 5.0, -3.0);
            Vector3 n = direction; //unit_vector(Vector3(0.0, 1.0, 0));
            double H = height; //2.0;
            double R = baseRadius;// 1.0;

            Point3 P0 = ray.origin;
            Vector3 d = ray.direction;

            Vector3 v = V - P0;

            double hipotenusa = sqrt(pow(H, 2.0) + pow(R, 2.0));
            double costeta = H / hipotenusa;
            double cos2teta = pow(costeta, 2.0);

            double a = pow(dot(d, n), 2.0) - (dot(d, d) * cos2teta);
            double b = (dot(v, d) * cos2teta) - (dot(v, n) * dot(d, n));
            double c = pow(dot(v, n), 2.0) - (dot(v, v)*cos2teta);

            double discriminant = b*b -a*c;

            if (discriminant <= 0) {
                return;
            }

            // if (a == 0) {
            //     cerr << "a = 0";
            // }

            auto t1 = (-1.0*b + sqrt(discriminant)) / (a);
            auto t2 = (-1.0*b - sqrt(discriminant)) / (a);

            if (t1 < 0 and t2 < 0) {
                return;
            }

            Point3 p1 = ray.pointAt(t1);
            Point3 p2 = ray.pointAt(t2);

            Vector3 vt1 = V - p1;
            Vector3 vt2 = V - p2;

            float h1 = dot(vt1, n);
            float h2 = dot(vt2, n);

            if ((h1 >= 0) and (h1 <= H)) {
                info.updateInterception(t1, this);
                //return 1.0;
            }

            if ((h2 >= 0) and (h2 <= H)) {
                info.updateInterception(t2, this);
                //return 1.0;
            }
            //cerr << "t1 " << t1 << " t2 " << t2 <<"\n ";
            //return -1.0;
            return;
        }

        Vector3 normalAt(Point3 &point) {
            // normal at given interception point?
            return unit_vector(Vector3(0, 1, 0));
        };
};