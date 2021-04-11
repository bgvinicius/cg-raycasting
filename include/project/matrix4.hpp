#ifndef MATRIX4_H
#define MATRIX4_H
#include <vector>

#include "vector3.hpp"

using namespace std;

class Matrix4 {
    public:
        vector<vector<float>> index {vector<float>{0, 0, 0, 0},  vector<float>{0, 0, 0, 0}, vector<float>{0, 0, 0, 0}, vector<float>{0, 0, 0, 0}};

        Matrix4() {};
        Matrix4(vector<vector<float>> index): index(index) {};
};

Matrix4 identityMatrix() {
    Matrix4 identity;
    identity.index[0][0] = 1;
    identity.index[1][1] = 1;
    identity.index[2][2] = 1;
    identity.index[3][3] = 1;

    return identity;
};

Matrix4 operator+(Matrix4 &u, Matrix4 &v) {
    Matrix4 resultado;
    resultado.index[0][0] = u.index[0][0] + v.index[0][0];
    resultado.index[0][1] = u.index[0][1] + v.index[0][1];
    resultado.index[0][2] = u.index[0][2] + v.index[0][2];
    resultado.index[0][3] = u.index[0][3] + v.index[0][3];
    resultado.index[1][0] = u.index[1][0] + v.index[1][0];
    resultado.index[1][1] = u.index[1][1] + v.index[1][1];
    resultado.index[1][2] = u.index[1][2] + v.index[1][2];
    resultado.index[1][3] = u.index[1][3] + v.index[1][3];
    resultado.index[2][0] = u.index[2][0] + v.index[2][0];
    resultado.index[2][1] = u.index[2][1] + v.index[2][1];
    resultado.index[2][2] = u.index[2][2] + v.index[2][2];
    resultado.index[2][3] = u.index[2][3] + v.index[2][3];
    resultado.index[3][0] = u.index[3][0] + v.index[3][0];
    resultado.index[3][1] = u.index[3][1] + v.index[3][1];
    resultado.index[3][2] = u.index[3][2] + v.index[3][2];
    resultado.index[3][3] = u.index[3][3] + v.index[3][3];

    return resultado;   
}


Matrix4 operator-(Matrix4 &u, Matrix4 &v){
    Matrix4 resultado;
    resultado.index[0][0] = u.index[0][0] - v.index[0][0];
    resultado.index[0][1] = u.index[0][1] - v.index[0][1];
    resultado.index[0][2] = u.index[0][2] - v.index[0][2];
    resultado.index[0][3] = u.index[0][3] - v.index[0][3];
    resultado.index[1][0] = u.index[1][0] - v.index[1][0];
    resultado.index[1][1] = u.index[1][1] - v.index[1][1];
    resultado.index[1][2] = u.index[1][2] - v.index[1][2];
    resultado.index[1][3] = u.index[1][3] - v.index[1][3];
    resultado.index[2][0] = u.index[2][0] - v.index[2][0];
    resultado.index[2][1] = u.index[2][1] - v.index[2][1];
    resultado.index[2][2] = u.index[2][2] - v.index[2][2];
    resultado.index[2][3] = u.index[2][3] - v.index[2][3];
    resultado.index[3][0] = u.index[3][0] - v.index[3][0];
    resultado.index[3][1] = u.index[3][1] - v.index[3][1];
    resultado.index[3][2] = u.index[3][2] - v.index[3][2];
    resultado.index[3][3] = u.index[3][3] - v.index[3][3];

    return resultado;   
}


Matrix4 operator*(Matrix4 &u, float v) {
    Matrix4 resultado;
    resultado.index[0][0] = u.index[0][0] * v;
    resultado.index[0][1] = u.index[0][1] * v;
    resultado.index[0][2] = u.index[0][2] * v;
    resultado.index[0][3] = u.index[0][3] * v;
    resultado.index[1][0] = u.index[1][0] * v;
    resultado.index[1][1] = u.index[1][1] * v;
    resultado.index[1][2] = u.index[1][2] * v;
    resultado.index[1][3] = u.index[1][3] * v;
    resultado.index[2][0] = u.index[2][0] * v;
    resultado.index[2][1] = u.index[2][1] * v;
    resultado.index[2][2] = u.index[2][2] * v;
    resultado.index[2][3] = u.index[2][3] * v;
    resultado.index[3][0] = u.index[3][0] * v;
    resultado.index[3][1] = u.index[3][1] * v;
    resultado.index[3][2] = u.index[3][2] * v;
    resultado.index[3][3] = u.index[3][3] * v;

    return resultado;   
    
}

Matrix4 operator*(float v, Matrix4 &u) {
    Matrix4 resultado;
    resultado.index[0][0] = u.index[0][0] * v;
    resultado.index[0][1] = u.index[0][1] * v;
    resultado.index[0][2] = u.index[0][2] * v;
    resultado.index[0][3] = u.index[0][3] * v;
    resultado.index[1][0] = u.index[1][0] * v;
    resultado.index[1][1] = u.index[1][1] * v;
    resultado.index[1][2] = u.index[1][2] * v;
    resultado.index[1][3] = u.index[1][3] * v;
    resultado.index[2][0] = u.index[2][0] * v;
    resultado.index[2][1] = u.index[2][1] * v;
    resultado.index[2][2] = u.index[2][2] * v;
    resultado.index[2][3] = u.index[2][3] * v;
    resultado.index[3][0] = u.index[3][0] * v;
    resultado.index[3][1] = u.index[3][1] * v;
    resultado.index[3][2] = u.index[3][2] * v;
    resultado.index[3][3] = u.index[3][3] * v;

    return resultado;   
    
}

Matrix4 operator*(Matrix4 &u, Matrix4 &v) {
    Matrix4 resultado;
    resultado.index[0][0] = u.index[0][0] * v.index[0][0] + u.index[0][1] * v.index[1][0] + u.index[0][2] * v.index [2][0] + u.index[0][3] * v.index[3][0];
    resultado.index[0][1] = u.index[0][0] * v.index[0][1] + u.index[0][1] * v.index[1][1] + u.index[0][2] * v.index [2][1] + u.index[0][3] * v.index[3][1];
    resultado.index[0][2] = u.index[0][0] * v.index[0][2] + u.index[0][1] * v.index[1][2] + u.index[0][2] * v.index [2][2] + u.index[0][3] * v.index[3][2];
    resultado.index[0][3] = u.index[0][0] * v.index[0][3] + u.index[0][1] * v.index[1][3] + u.index[0][2] * v.index [2][3] + u.index[0][3] * v.index[3][3];
    resultado.index[1][0] = u.index[1][0] * v.index[0][0] + u.index[1][1] * v.index[1][0] + u.index[1][2] * v.index [2][0] + u.index[1][3] * v.index[3][0];
    resultado.index[1][1] = u.index[1][0] * v.index[0][1] + u.index[1][1] * v.index[1][1] + u.index[1][2] * v.index [2][1] + u.index[1][3] * v.index[3][1];
    resultado.index[1][2] = u.index[1][0] * v.index[0][2] + u.index[1][1] * v.index[1][2] + u.index[1][2] * v.index [2][2] + u.index[1][3] * v.index[3][2];
    resultado.index[1][3] = u.index[1][0] * v.index[0][3] + u.index[1][1] * v.index[1][3] + u.index[1][2] * v.index [2][3] + u.index[1][3] * v.index[3][3]; 
    resultado.index[2][0] = u.index[2][0] * v.index[0][0] + u.index[2][1] * v.index[1][0] + u.index[2][2] * v.index [2][0] + u.index[2][3] * v.index[3][0];
    resultado.index[2][1] = u.index[2][0] * v.index[0][1] + u.index[2][1] * v.index[1][1] + u.index[2][2] * v.index [2][1] + u.index[2][3] * v.index[3][1];
    resultado.index[2][2] = u.index[2][0] * v.index[0][2] + u.index[2][1] * v.index[1][2] + u.index[2][2] * v.index [2][2] + u.index[2][3] * v.index[3][2];
    resultado.index[2][3] = u.index[2][0] * v.index[0][3] + u.index[2][1] * v.index[1][3] + u.index[2][2] * v.index [2][3] + u.index[2][3] * v.index[3][3];
    resultado.index[3][0] = u.index[3][0] * v.index[0][0] + u.index[3][1] * v.index[1][0] + u.index[3][2] * v.index [2][0] + u.index[3][3] * v.index[3][0];
    resultado.index[3][1] = u.index[3][0] * v.index[0][1] + u.index[3][1] * v.index[1][1] + u.index[3][2] * v.index [2][1] + u.index[3][3] * v.index[3][1];
    resultado.index[3][2] = u.index[3][0] * v.index[0][2] + u.index[3][1] * v.index[1][2] + u.index[3][2] * v.index [2][2] + u.index[3][3] * v.index[3][2];
    resultado.index[3][3] = u.index[3][0] * v.index[0][3] + u.index[3][1] * v.index[1][3] + u.index[3][2] * v.index [2][3] + u.index[3][3] * v.index[3][3];

   return resultado;
}

Point3 operator*(Matrix4 &u, Point3 &p){
    return Point3
    (u.index[0][0]*p.x + u.index[0][1]*p.y + u.index[0][2]*p.z + u.index[0][3],
    u.index[1][0]*p.x + u.index[1][1]*p.y + u.index[1][2]*p.z + u.index[1][3],
    u.index[2][0]*p.x + u.index[2][1]*p.y + u.index[2][2]*p.z + u.index[2][3]);


}
Point3 operator*(Point3 &p, Matrix4 &u){
    return Point3
    (u.index[0][0]*p.x + u.index[0][1]*p.y + u.index[0][2]*p.z + u.index[0][3],
    u.index[1][0]*p.x + u.index[1][1]*p.y + u.index[1][2]*p.z + u.index[1][3],
    u.index[2][0]*p.x + u.index[2][1]*p.y + u.index[2][2]*p.z + u.index[2][3]);


}

Vector3 operator*(Matrix4 &u, Vector3 &v) {
    return Vector3(u.index[0][0]*v.x + u.index[0][1]*v.y + u.index[0][2]*v.z,
    u.index[1][0]*v.x + u.index[1][1]*v.y + u.index[1][2]*v.z,
    u.index[2][0]*v.x + u.index[2][1]*v.y + u.index[2][2]*v.z);

}

Vector3 operator*(Vector3 &v, Matrix4 &u) {
    return Vector3(u.index[0][0]*v.x + u.index[0][1]*v.y + u.index[0][2]*v.z,
    u.index[1][0]*v.x + u.index[1][1]*v.y + u.index[1][2]*v.z,
    u.index[2][0]*v.x + u.index[2][1]*v.y + u.index[2][2]*v.z);

}

#endif