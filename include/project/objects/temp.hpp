#include "../object.hpp"

class Temp: public Object {
    public:
        // your constructor
        Temp() {}

        void intercepts(Ray &ray, InterceptionInfo &info) {
            // ray intercepts this object?
        }

        Vector3 normalAt(Point3 &point) {
            // normal at given interception point?
            return unit_vector(Vector3(0, 1, 0));
        };
};