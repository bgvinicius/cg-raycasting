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
};

Point3 translate_point(Point3 &p, Vector3 &v){
    Transform t;
    Matrix4 matriz_trans = t.translation_matrix(v);
    return matriz_trans*p;

};