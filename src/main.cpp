#include <iostream>
#include "project/vector3.hpp"
#include "project/objects/sphere.hpp"
#include "project/objects/cylinder.hpp"
#include "project/objects/cone.hpp"
#include <vector>
#include <math.h>
#include "project/camera.hpp"
#include "project/object.hpp"
#include "project/objects/triangle.hpp"
#include "project/objects/meshobject.hpp"
#include "project/objects/plane.hpp"
#include "project/lights/material.hpp"

using namespace std;

void write_color(std::ostream &out, float r, float g, float b) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(r) << ' '
        << static_cast<int>(g) << ' '
        << static_cast<int>(b) << '\n';
}

// class TriangleFace {
//     public:
//         Point3 v1, v2, v3;
//         Point3 rgb;

//         TriangleFace(): v1(Point3(0, 0, 0)), v2(Point3(0, 0, 0)), v3(Point3(0, 0, 0)), rgb(Point3(0, 0, 0)) {

//         }
//         TriangleFace(Point3 v1, Point3 v2, Point3 v3, Point3 rgb): v1(v1), v2(v2), v3(v3), rgb(rgb) {}

//         // void show() {
//         //     cout << "v1: " << v1 << " v2: " << v2 << " v3: " << v3 << "\n";
//         // }
// };

float computeLighting(Vector3 &normal, Vector3 &pixelToEye, int s) {
    float i = 0.5;

    Vector3 lightD(0, 1, 0);
    float n_dot_l = dot(normal, lightD);

    if (n_dot_l > 0) {
        i += 0.5 * (n_dot_l / (normal.length() * lightD.length()));
    }

    Vector3 R = ((2.0 * normal) * dot(normal, lightD)) - lightD;
    float rdotv = dot(R, pixelToEye);

    if (rdotv > 0) {
        i += 0.5 * pow(rdotv / (R.length() * pixelToEye.length()), s);
    }

    return i;
}

float computeLightingFloor(Vector3 &normal, Vector3 &pixelToEye, int s, Point3 &pontoInter, vector<Sphere> &esfs, int nesfs) {
    float i = 0.5;

    Vector3 lightD(0, 1, 0);

    //Ray shadowRay = Ray(pontoInter, lightD);
    // if (doesIntercept(esfs, nesfs, shadowRay)) {
    //     //cerr << "a";
    //     return i;
    // }

    float n_dot_l = dot(normal, lightD);

    if (n_dot_l > 0) {
        //cerr << "aq";
        i += 0.8 * (n_dot_l / (normal.length() * lightD.length()));
    }

    Vector3 R = ((2.0 * normal) * dot(normal, lightD)) - lightD;
    float rdotv = dot(R, pixelToEye);

    if (rdotv > 0) {
        i += 0.8 * pow(rdotv / (R.length() * pixelToEye.length()), s);
    }


    //cerr << i << "\n";
    return i;
}

void render(vector<TriangleFace> &triangles) {
    Point3 eye = Point3(0, 0, 0);
    Point3 at = Point3(0, 0, -1);
    Point3 up = Point3(0, 1, -1);

    Camera c = Camera(eye, at, up);

    //vector<TriangleFace> newFaces = {};

    // for (int i =0; i < tr.size(); i++) {
    //     TriangleFace f = tr[i];

    //     TriangleFace f2 = TriangleFace();

    //     f2.v1 = c.worldToCamera * f.v1;
    //     f2.v2 = c.worldToCamera * f.v2;
    //     f2.v3 = c.worldToCamera * f.v3;
    //     f2.rgb.x = f.rgb.x;
    //     f2.rgb.y = f.rgb.y;
    //     f2.rgb.z = f.rgb.z;

    //     newFaces.push_back(f2);
    // }

    eye = Point3(0, 0, 0);

    const int width = 800;
    const int height = 800;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    float x_max = 4.0;
    float x_min = -4.0;
    float y_min = -4.0;
    float y_max = 4.0;

    float delt_x = ((x_max - x_min) / width);
    float delt_y = ((y_max - y_min) / height);

    std::cerr << "renderizando...\n";

    vector<Object*> esfs;

    Material m = Material(reflectionFromRGB(100, 100, 100), reflectionFromRGB(100, 100, 100), reflectionFromRGB(100, 100, 100));

    Sphere esf1 = Sphere(Point3(0.0, 0.0, -1.0), 0.5, m);
    Sphere esf2 = Sphere(Point3(1.0, 0.0, -1.5), 0.5, m);
    Sphere esf3 = Sphere(Point3(2.0, 1.5, -2.5), 1, m);
    Sphere esf4 = Sphere(Point3(4.0, 1.5, -7), 3, m);
    Cylinder cil1 = Cylinder(Point3(-2, 0, -3.0), 1.0f, 1.0f, Vector3(0, 1, 0), m);
    Cone cone1 = Cone(Point3(0, -3, -3.0), Vector3(0, 1.0, 0), 2.0, 1.0, m);
    MeshObject mesh = makeCube(20, 24, 0, 4, -11, -13);
    Plane plane = Plane(Point3(0, -4, 0), Vector3(0, 1, 0), m);
    
    esfs.push_back(&esf1);
    esfs.push_back(&esf2);
    esfs.push_back(&esf3);
    esfs.push_back(&esf4);
    esfs.push_back(&cil1);
    esfs.push_back(&cone1);
    esfs.push_back(&mesh);
    esfs.push_back(&plane);

    int o = esfs.size();

    for (int h = height, i = 0; h >= 0; h--, i++) {
        for (int w = 0; w < width; w++) {
            // w anda dentro duma linha, i passa linha de cima pra baixo
            float x_pos = x_min + (delt_x / 2.0) + (w * delt_x);
            float y_pos = y_max - (delt_y / 2.0) - (i * delt_y);
            float z_pos = -1;

            // raio saindo da camera (eye) indo ate o centro do pixel no canvas
            //Vector3 direction(x_pos, y_pos, z_pos);

            Point3 pix = Point3(x_pos, y_pos, z_pos);
            Vector3 direction = Vector3(x_pos, y_pos, z_pos); //  pix - eye;

            Ray raio(eye, direction);

            InterceptionInfo interception(raio);
            for (int e = 0; e < o; e++) {
                esfs[e]->intercepts(raio, interception);
            }

            if (interception.valid) {
                Point3 hitPoint = interception.getHitPoint();
                //Vector3 normal = interception.hitObject->normalAt(hitPoint);
                //Vector3 interToEye = direction.reverse();
                Vector3 b = direction * -1;
                //float light = computeLighting(normal, b, 500);

                Material m = interception.hitObject->material;

                write_color(std::cout, m.ambient.r * 255, m.ambient.g * 255, m.ambient.b * 255);
            } else {
                write_color(std::cout, 255, 255, 255);
            }
        }
    }
}

int main() {

    for (int i = 0; i < 4; i++) {
        string t;
        getline(cin, t);
        //cin >> t;

        //cout << t << "\n";
    }

    vector <Point3> mycube;

    for (int i = 0; i < 24; i++) {
        string v;
        Point3 tp(0, 0, 0);
    
        cin >> v;
        if (v.compare("v") == 0) {
            cin >> tp.x >> tp.y >> tp.z;

            // if (tp.y == 4) {
            //     tp.y = tp.y - 2;
            // }

            // if (tp.x == 18) {
            //     tp.x = tp.x - 2;
            // }

            // if (tp.z == -15) {
            //     tp.z = -13;
            // }
            //tp.show();
            mycube.push_back(tp);
        } else {
//            cout << "fim\n";
            break;
        }
    } 

    vector <TriangleFace> mycubefaces;


    // for (int i = 0; i < 12; i++) {
    //     string v;

    //     int p1, p2, p3;

    //     cin >> v >> p1 >> p2 >> p3;

    //     Point3 v1 = mycube[p1-1];
    //     Point3 v2 = mycube[p2-1];
    //     Point3 v3 = mycube[p3-1];

    //     TriangleFace face;

    //     face.v1 = v1;
    //     face.v2 = v2;
    //     face.v3 = v3;

    //     mycubefaces.push_back(face);
    // }

    // for (int i = 0; i < 12; i++ ){
    //     TriangleFace face = mycubefaces[i];

    //     cout << "face " << i << "\n";
    //     cout << "v1: " << "(" << face.v1.x << ", " << face.v1.y << ", " << face.v1.z << ")\n";
    //     cout << "v2: " << "(" << face.v2.x << ", " << face.v2.y << ", " << face.v2.z << ")\n";
    //     cout << "v3: " << "(" << face.v3.x << ", " << face.v3.y << ", " << face.v3.z << ")\n";

    // }

    render(mycubefaces);

    // while (true) {

    // }
    //render();
}