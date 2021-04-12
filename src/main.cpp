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
#include "project/lights/light.hpp"

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

Component getColor(vector<Light*> &lights, Vector3 &hitPointToObserver, Point3 &hitPoint, Object &hitObject) {
    Component currentColor = Component(0, 0, 0);

    for (int i = 0; i < lights.size(); i++) {
        //Point3 hitPoint = getHitPoint();
        Vector3 normal = hitObject.normalAt(hitPoint);
        
        Component contribution = lights[i]->contribution(normal, hitPoint, hitPointToObserver, hitObject.material);

        currentColor.r += contribution.r;
        currentColor.g += contribution.g;
        currentColor.b += contribution.b;
    }

    return currentColor;
}

void render(vector<TriangleFace> &triangles) {
    Point3 eye = Point3(0, 0, 5);
    Point3 at = Point3(0, 0, 0);
    Point3 up = Point3(0, 1, 0);

    Camera camera = Camera(eye, at, up);

    eye = Point3(0, 0, 0);

    const int width = 1366;
    const int height = 768;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    float x_max = 4.0;
    float x_min = -4.0;
    float y_min = -4.0;
    float y_max = 4.0;

    float delt_x = ((x_max - x_min) / width);
    float delt_y = ((y_max - y_min) / height);

    std::cerr << "renderizando...\n";

    vector<Object*> esfs;

    Material m1 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(100, 100, 100), reflectionFromRGB(100, 100, 100), 2.0);
    Material m2 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(230, 100, 233), reflectionFromRGB(80, 70, 200), 3.0);
    Material m3 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(230, 20, 40), reflectionFromRGB(100, 90, 230), 3.0);
    Material m4 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(100, 78, 230), reflectionFromRGB(230, 230, 230), 2.5);

    Material planeFloor = Material(reflectionFromRGB(70, 46, 26), reflectionFromRGB(70, 46, 26), reflectionFromRGB(70, 46, 26), 1.0);

    Sphere esf1 = Sphere(Point3(0.0, 0.0, -1.0), 0.5, m1);
    Sphere esf2 = Sphere(Point3(1.0, 0.0, -1.5), 0.5, m2);
    Sphere esf3 = Sphere(Point3(2.0, 1.5, -2.5), 1, m3);
    Sphere esf4 = Sphere(Point3(4.0, 1.5, -7), 3, m2);
    Cylinder cil1 = Cylinder(Point3(-2, 0, -3.0), 1.0f, 1.0f, Vector3(0, 1, 0), m3);
    Cone cone1 = Cone(Point3(0, -3, -3.0), Vector3(0, 1.0, 0), 2.0, 1.0, m2);
    MeshObject mesh = makeCube(-2, 2, -2.0, 2.0, 2.0, -2.0, m4, m3, m1, m2);
    // mesh.setMaterial(m4);
    Plane plane = Plane(Point3(0, -7, 0), Vector3(0, 1, 0), planeFloor);

    Cylinder xAx = Cylinder(Point3(0, 0, 0), 0.02, 10, Vector3(1, 0, 0), m3);
    Cylinder yAx = Cylinder(Point3(0, 0, 0), 0.02, 10, Vector3(0, 1, 0), m3);
    Cylinder zAx = Cylinder(Point3(0, 0, 0), 0.02, 10, Vector3(0, 0, 1), m3);

    Vector3 trVector = Vector3(4, 4, -5);
    //Vector3 goBack = trVector.reverse();
    Vector3 XZ_AXIS = Vector3(0, 0, 1);

    mesh.meshTranslate(trVector);
    trVector = Vector3(1, 0, 0);
    mesh.meshShear(XZ_AXIS, trVector, 1);

    // mesh.meshScale(trVector, mesh.mesh[0].v1);
    // mesh.meshRotate(X_AXIS, 1.0);
    // mesh.meshTranslate(goBack);
    
    esfs.push_back(&esf1);
    esfs.push_back(&esf2);
    esfs.push_back(&esf3);
    esfs.push_back(&esf4);
    esfs.push_back(&cil1);
    esfs.push_back(&cone1);
    esfs.push_back(&mesh);
    // esfs.push_back(&xAx);
    // esfs.push_back(&yAx);
    // esfs.push_back(&zAx);
    esfs.push_back(&plane);

    int o = esfs.size();


    AmbientLight ambientLight = AmbientLight(0.1);

    PointLight pointLight = PointLight(Point3(-10, 10, 10), reflectionFromRGB(255, 255, 255), reflectionFromRGB(255, 255, 255));

    vector<Light*> lights = {
        &ambientLight,
        &pointLight
    };

    // ===== WORLD COORDINATES TO CAMERA COORDINATES TRANSFORMATION =======

    pointLight.toCamera(camera.worldToCamera);

    for (int i = 0; i < esfs.size(); i++) {
        esfs[i]->toCamera(camera.worldToCamera);
    }

    for (int h = height, i = 0; h >= 0; h--, i++) {
        for (int w = 0; w < width; w++) {
            // w anda dentro duma linha, i passa linha de cima pra baixo
            float x_pos = x_min + (delt_x / 2.0) + (w * delt_x);
            float y_pos = y_max - (delt_y / 2.0) - (i * delt_y);
            float z_pos = -2;

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
                Vector3 hitPointToObserver = unit_vector(raio.direction.reverse());
                Point3 hitPoint = interception.getHitPoint();
                // Object *hitObject = interception.hitObject;
    
                Component finalColor = getColor(lights, hitPointToObserver, hitPoint, *interception.hitObject);

                //Material m = interception.hitObject->material;

                // if (finalColor.r > 1 or finalColor.g > 1 or finalColor.b > 1) {
                //     cerr << "ops";
                // }
                finalColor.r = min(finalColor.r, 1.0f);
                finalColor.g = min(finalColor.g, 1.0f);
                finalColor.b = min(finalColor.b, 1.0f);

                write_color(std::cout, finalColor.r * 255, finalColor.g * 255, finalColor.b * 255);
            } else {
                write_color(std::cout, 255, 255, 255);
            }
        }
    }
}

int main() {

//     for (int i = 0; i < 4; i++) {
//         string t;
//         getline(cin, t);
//         //cin >> t;

//         //cout << t << "\n";
//     }

//     vector <Point3> mycube;

//     for (int i = 0; i < 24; i++) {
//         string v;
//         Point3 tp(0, 0, 0);
    
//         cin >> v;
//         if (v.compare("v") == 0) {
//             cin >> tp.x >> tp.y >> tp.z;

//             // if (tp.y == 4) {
//             //     tp.y = tp.y - 2;
//             // }

//             // if (tp.x == 18) {
//             //     tp.x = tp.x - 2;
//             // }

//             // if (tp.z == -15) {
//             //     tp.z = -13;
//             // }
//             //tp.show();
//             mycube.push_back(tp);
//         } else {
// //            cout << "fim\n";
//             break;
//         }
//     } 

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