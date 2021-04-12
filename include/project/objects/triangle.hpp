#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../object.hpp"

class TriangleFace: public Object {
    public:
        // your constructor

        Point3 v1, v2, v3;
        
        // the three vertices, which should be given following counter clockwise order!
        // this is needed for the normal calculations.
        TriangleFace(Point3 v1, Point3 v2, Point3 v3): v1(v1), v2(v2), v3(v3) {
            
        }

        TriangleFace(Point3 v1, Point3 v2, Point3 v3, Material material): Object(material), v1(v1), v2(v2), v3(v3) {
        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
                const float EPSILON = 0.0000001;
                Point3 vertex0 = v1;
                Point3 vertex1 = v2;  
                Point3 vertex2 = v3;
                float a,f,u,v;
                Vector3 edge1 = vertex1 - vertex0;
                Vector3 edge2 = vertex2 - vertex0;
                Vector3 h =  cross(ray.direction, edge2);// rayVector.crossProduct(edge2);
                a =  dot(edge1, h);// edge1.dotProduct(h);
                if (a > -EPSILON && a < EPSILON)
                    return;    // This ray is parallel to this triangle.
                f = 1.0/a;
                Vector3 s = ray.origin - vertex0;// rayOrigin - vertex0;
                u = f * dot(s, h); // f * s.dotProduct(h);
                if (u < 0.0 || u > 1.0)
                    return;
                Vector3 q = cross(s, edge1); //s.crossProduct(edge1);
                v = f * dot(ray.direction, q); //f * rayVector.dotProduct(q);
                if (v < 0.0 || u + v > 1.0)
                    return;
                // At this stage we can compute t to find out where the intersection point is on the line.
                float t = f * dot(edge2, q); //f * edge2.dotProduct(q);
                if (t > EPSILON) // ray intersection
                {
                    // outIntersectionPoint = rayOrigin + rayVector * t;
                    info.updateInterception(t, this);
                    return;
                }
                else // This means that there is a line intersection but not a ray intersection.
                    return;
        }

        Vector3 normalAt(Point3 &point) {
            // normal at given interception point?
            Vector3 w1 = v2 - v1;
            Vector3 w2 = v3 - v1;

            Vector3 N = cross(w1, w2);

            return unit_vector(N);
        };

        void toCamera(Matrix4 &toCamera) {
            this->v1 = this->v1 * toCamera;
            this->v2 = this->v2 * toCamera;
            this->v3 = this->v3 * toCamera;
        }
};

#endif