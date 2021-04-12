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

        void meshTranslate(Vector3 &dir){
            for (TriangleFace &tf : mesh){
                tf.v1=translatePoint(tf.v1, dir);
                tf.v2=translatePoint(tf.v2, dir);
                tf.v3=translatePoint(tf.v3, dir);
            }
        }

        void meshRotate(Vector3 &axis, float teta) {
            for (TriangleFace &tf : mesh) {
                tf.v1 = rotationPoint(axis, tf.v1, teta); 
                tf.v2 = rotationPoint(axis, tf.v2, teta);
                tf.v3 = rotationPoint(axis, tf.v3, teta);
            }
        }

        void toCamera(Matrix4 &toCamera) {
            for (int i = 0; i < mesh.size(); i++) {
                mesh[i].toCamera(toCamera);
            }
        }
        
        void meshShear(Vector3 &plane, Vector3 &dir, float t){
            for (TriangleFace &tf : mesh) {
                tf.v1 = shear(plane, dir, tf.v1, t); 
                tf.v2 = shear(plane, dir, tf.v2, t);
                tf.v3 = shear(plane, dir, tf.v3, t);
            }

        }

        void meshScale (Vector3 &scale, Point3 &ancor){
            for (TriangleFace &tf : mesh) {
                tf.v1 = scalePoint(scale, ancor, tf.v1); 
                tf.v2 = scalePoint(scale, ancor, tf.v2);
                tf.v3 = scalePoint(scale, ancor, tf.v3);
            }
        }

        void meshReflection (Vector3 &plane){
            for (TriangleFace &tf : mesh) {
                tf.v1 = reflectionPoint(plane, tf.v1); 
                tf.v2 = reflectionPoint(plane, tf.v2);
                tf.v3 = reflectionPoint(plane, tf.v3);
            }

        }
}; 

MeshObject makeCube(float cube_xmin, float cube_xmax, float cube_ymin, float cube_ymax, float cube_zmin, float cube_zmax, Material &m1, Material &m2, Material &m3, Material &m4) {
    // int cube_xmin = 20;
    // int cube_xmax = 24;
    // int cube_ymin = 0;
    // int cube_ymax = 4;
    // int cube_zmin = -11;
    // int cube_zmax = -13;

    return MeshObject({
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmin), m1), // frente
        TriangleFace(Point3(cube_xmin, cube_ymax, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymax, cube_zmin), m1), // frente
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmax), Point3(cube_xmin, cube_ymin, cube_zmax), m2), // lado esquerdo
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmax), m2), // esq
        TriangleFace(Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmin), m3), // dir
        TriangleFace(Point3(cube_xmax, cube_ymax, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmax), m3), // dir
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmin, cube_ymax, cube_zmax), m4), // tras
        TriangleFace(Point3(cube_xmin, cube_ymax, cube_zmax), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmax), m4), // tras
    });
}

MeshObject makeRet(float ret_xmin, float ret_xmax, float ret_ymin, float ret_ymax, float ret_zmin, Material &m){
    return MeshObject({
        TriangleFace(Point3(ret_xmin, ret_ymin, ret_zmin), Point3(ret_xmax, ret_ymin, ret_zmin), Point3(ret_xmin, ret_ymax, ret_zmin), m),
        TriangleFace(Point3(ret_xmax, ret_ymin, ret_zmin), Point3(ret_xmax, ret_ymax, ret_zmin), Point3(ret_xmin, ret_ymax, ret_zmin), m),
    });
}
