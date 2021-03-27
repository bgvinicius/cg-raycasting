#include "vector3.hpp"
#include "matrix4.hpp"
#include "point3.hpp"


class Transform{
    public:
        Matrix4 translation_matrix (Vector3 &v){
            Matrix4 resultado;
            resultado.index[0][0] = 1;
            resultado.index[1][1] = 1;
            resultado.index[2][2] = 1;
            resultado.index[3][3] = 1; 
            resultado.index[0][3] = v.x;
            resultado.index[1][3] = v.y;
            resultado.index[2][3] = v.z;

            return resultado; 
        }

        Matrix4 scaling_matrix(Vector3 &v, Point3 &p){
            Matrix4 resultado;
            resultado.index[0][0] = v.x;
            resultado.index[1][1] = v.y;
            resultado.index[2][2] = v.z;
            resultado.index[3][3] = 1; 
            resultado.index[0][3] = (1-v.x) * p.x;
            resultado.index[1][3] = (1-v.y) * p.y;
            resultado.index[2][3] = (1-v.z) * p.z;

            return resultado; 
        }

       Matrix4 shearing_matrix(Vector3 &v, Vector3 &u, float x) {
            Matrix4 resultado = identity();
            if (v.z == 1 and u.x == 1) {
                resultado.index[0][1] = x;
            }
            if (v.z == 1 and u.y == 1) {
                resultado.index[1][0] = x;
            }
            if (v.y == 1 and u.x == 1) {
                resultado.index[0][2] = x;
            }
            if (v.y == 1 and u.z == 1) {
                resultado.index[2][0] = x;
            }
            if (v.x == 1 and u.y == 1) {
                resultado.index[1][2] = x;
            }
            if (v.x == 1 and u.z == 1) {
                resultado.index[2][1] = x;
            }
        return resultado;
        }

};

Point3 translate_point(Point3 &p, Vector3 &v){
    Transform t;
    Matrix4 matrix_trans = t.translation_matrix(v);
    return matrix_trans*p;
};

Point3 translate_point(Vector3 &v, Point3 &p){
    Transform t;
    Matrix4 matrix_trans = t.translation_matrix(v);
    return matrix_trans*p;
};

// V é o vetor da direção da translação e u é o vetor a ser transladado.
Vector3 translate_vector(Vector3 &v, Vector3 &u){
    Transform t;
    Matrix4 matrix_trans = t.translation_matrix(v);
    return matrix_trans*u;
};

// V é o vetor de escala, p é a âncora, e x é o ponto a ser escalonado.
Point3 scale_point (Vector3 &v, Point3 &p, Point3 &x){
    Transform t;
    Matrix4 matrix_scale = t.scaling_matrix(v, p);
    return matrix_scale*x;
}

Point3 shear(Vector3 &v, Vector3 &u, Point3 &p, float x) {
    Transform t;
    Matrix4 matrix_shear = t.shearing_matrix(v, u, x);
    return matrix_shear * p;
}



