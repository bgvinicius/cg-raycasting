#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "vector3.hpp"
#include "matrix4.hpp"
#include "point3.hpp"
#include <cmath>


class Transform{
    public:
        Matrix4 translationMatrix (Vector3 &v){
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

        Matrix4 scalingMatrix(Vector3 &v, Point3 &p){
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

       Matrix4 shearingMatrix(Vector3 &v, Vector3 &u, float x) {
            Matrix4 resultado = identityMatrix();
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

        Matrix4 rotationMatrix(Vector3 &v, float t){
            Matrix4 resultado = identityMatrix();
            if(v.x==1){
                resultado.index[1][1] = cos(t);
                resultado.index[2][2] = cos(t);
                resultado.index[1][2] = -sin(t);
                resultado.index[2][1] = sin(t);
            }
            if(v.y==1){
                resultado.index[0][0] = cos(t);
                resultado.index[2][2] = cos(t);
                resultado.index[0][2] = sin(t);
                resultado.index[2][0] = -sin(t);
            }
            if(v.z==1){
                resultado.index[0][0] = cos(t);
                resultado.index[1][1] = cos(t);
                resultado.index[0][1] = -sin(t);
                resultado.index[1][0] = sin(t);
            }
        }

        Matrix4 reflectionMatrix(Vector3 &plane){
            Matrix4 resultado = identityMatrix();
            if(plane.y==1){
                resultado.index[1][1]=-1;
            }
            if(plane.x==1){
                resultado.index[0][0]=-1;
            }
            if(plane.z==1){
                resultado.index[2][2]=-1;
            }
            return resultado;
        }

};

Point3 translatePoint(Point3 &p, Vector3 &v){
    Transform t;
    Matrix4 matrix_trans = t.translationMatrix(v);
    return matrix_trans*p;
};

Point3 translatePoint(Vector3 &v, Point3 &p){
    Transform t;
    Matrix4 matrix_trans = t.translationMatrix(v);
    return matrix_trans*p;
};

// V é o vetor da direção da translação e u é o vetor a ser transladado.
Vector3 translateVector(Vector3 &v, Vector3 &u){
    Transform t;
    Matrix4 matrix_trans = t.translationMatrix(v);
    return matrix_trans*u;
};

// V é o vetor de escala, p é a âncora, e x é o ponto a ser escalonado.
Point3 scalePoint (Vector3 &v, Point3 &p, Point3 &x){
    Transform t;
    Matrix4 matrix_scale = t.scalingMatrix(v, p);
    return matrix_scale*x;
};

// V é o plano de cisalhamento, u é a direção, x é valor do cisalhamento, e p é ponto que vai sofrer a transformação
Point3 shear(Vector3 &v, Vector3 &u, Point3 &p, float x) {
    Transform t;
    Matrix4 matrix_shear = t.shearingMatrix(v, u, x);
    return matrix_shear * p;
};

Point3 rotationPoint(Vector3 &v, Point3 &p, float theta){
    Transform t;
    Matrix4 matrix_rotation = t.rotationMatrix(v,theta);
    return matrix_rotation *p;
};

Vector3 rotationVector(Vector3 &v, Vector3 &u, float theta){
    Transform t;
    Matrix4 matrix_rotation = t.rotationMatrix(v,theta);
    return matrix_rotation *u;
};

Point3 reflectionPoint(Vector3 &plane, Point3 &p){
    Transform t;
    Matrix4 matrix_reflection = t.reflectionMatrix(plane);
    return matrix_reflection * p;
}

/*Point3 reflection(){

};*/

#endif


