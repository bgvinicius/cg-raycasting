#include "../object.hpp"
#include "../objects/triangle.hpp"
#include <stdexcept>
#include <vector>
#include "../transform.hpp"

using namespace std;

class MeshObject: public Object {
    public:
        vector<TriangleFace> mesh;

        MeshObject(vector<TriangleFace> mesh): mesh(mesh) {
        }

        MeshObject(vector<TriangleFace> mesh, Material material): mesh(mesh), Object(material) {
            setMaterial(material);
        }

        MeshObject() {}

        void setMaterial(Material material) {
            for (int i = 0; i < mesh.size(); i++) {
                mesh[i].material = material;
            }
        }

        // add a new mesh to this object. Return this to enable chaining.
        MeshObject& add(TriangleFace &face) {
            mesh.push_back(face);

            return *this;
        }

        void intercepts(Ray &ray, InterceptionInfo &info) {
            for (int i = 0; i < mesh.size(); i++) {
                mesh[i].intercepts(ray, info);
            }
        }

        Vector3 normalAt(Point3 &point) {
            throw std::invalid_argument(
                "We can't compute the normal for a mesh object. We must delegate to apropriate triangle face."
            );
        }

        /*MeshObject meshTranslate(Vector3 &dir){
            Transform t;
            for (TriangleFace tf:mesh){
               tf.v1=translatePoint(tf.v1, dir);
               tf.v2=translatePoint(tf.v2, dir);
               tf.v3=translatePoint(tf.v3, dir);
            }
        }*/
}; 

MeshObject makeCube(int cube_xmin, int cube_xmax, int cube_ymin, int cube_ymax, int cube_zmin, int cube_zmax) {
    // int cube_xmin = 20;
    // int cube_xmax = 24;
    // int cube_ymin = 0;
    // int cube_ymax = 4;
    // int cube_zmin = -11;
    // int cube_zmax = -13;

    return MeshObject({
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmin)), // frente
        TriangleFace(Point3(cube_xmin, cube_ymax, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymax, cube_zmin)), // frente
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmax), Point3(cube_xmin, cube_ymin, cube_zmax)), // lado esquerdo
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmax)), // esq
        TriangleFace(Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmin)), // dir
        TriangleFace(Point3(cube_xmax, cube_ymax, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmax)), // dir
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmin, cube_ymax, cube_zmax)), // tras
        TriangleFace(Point3(cube_xmin, cube_ymax, cube_zmax), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmax)), // tras
    });
}