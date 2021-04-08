#include "vector3.hpp"
#include "matrix4.hpp"
#include <vector>

class Camera {
    public:
        Point3 position, at, up;
        Matrix4 worldToCamera;
        
        Camera(Point3 &position, Point3 &at, Point3 &up): position(position), at(at), up(up) {
            // vetor k'
            
            Vector3 k = unit_vector(position - at);
            Vector3 vup = up - position;

            // vetor I, sem estar normalizado
            Vector3 I = cross(vup, k);
            Vector3 i = unit_vector(I);

            // vetor j'
            Vector3 j = cross(k, i);

            Vector3 auxP = Vector3(position.x, position.y, position.z);

            vector<vector<float>> m = {
                vector<float>{i.x, i.y, i.z, -1.0f*dot(auxP, i)},  
                vector<float>{j.x, j.y, j.z, -1.0f*dot(auxP, j)}, 
                vector<float>{k.x, k.y, k.z, -1.0f*dot(auxP, k)}, 
                vector<float>{0, 0, 0, 1}
            };

            worldToCamera = Matrix4(m);

            std::cerr << "\n=== CAMERA VECTORS ===\n";
            std::cerr << "k: " << k << "\n"; 
            std::cerr << "i: " << i << "\n";
            std::cerr << "j: " << j << "\n";
        }
};