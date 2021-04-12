#include <iostream>
#include "../include/project/vector3.hpp"
#include "../include/project/objects/sphere.hpp"
#include "../include/project/objects/cylinder.hpp"
#include "../include/project/objects/cone.hpp"
#include <vector>
#include <math.h>
#include "../include/project/camera.hpp"
#include "../include/project/object.hpp"
#include "../include/project/objects/triangle.hpp"
#include "../include/project/objects/meshobject.hpp"
#include "../include/project/objects/plane.hpp"
#include "../include/project/lights/material.hpp"
#include "../include/project/lights/light.hpp"

using namespace std;

void write_color(std::ostream &out, float r, float g, float b) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(r) << ' '
        << static_cast<int>(g) << ' '
        << static_cast<int>(b) << '\n';
}

float computeLightingFloor(Vector3 &normal, Vector3 &pixelToEye, int s, Point3 &pontoInter, vector<Sphere> &objects, int nobjects) {
    float i = 0.5;

    Vector3 lightD(0, 1, 0);

    //Ray shadowRay = Ray(pontoInter, lightD);
    // if (doesIntercept(objects, nobjects, shadowRay)) {
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

void render() {
    Point3 eye = Point3(0, 0, 8);
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

    vector<Object*> objects;

    Material m1 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(100, 100, 100), reflectionFromRGB(100, 100, 100), 2.0);
    Material m2 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(230, 100, 233), reflectionFromRGB(80, 70, 200), 3.0);
    Material m3 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(230, 20, 40), reflectionFromRGB(100, 90, 230), 3.0);
    Material m4 = Material(reflectionFromRGB(255, 255, 255), reflectionFromRGB(100, 78, 230), reflectionFromRGB(230, 230, 230), 2.5);

    Material planeFloor = Material(reflectionFromRGB(70, 46, 26), reflectionFromRGB(70, 46, 26), reflectionFromRGB(70, 46, 26), 1.0);

    //Sphere esf1 = Sphere(Point3(0.0, 0.0, -1.0), 0.5, m1);
    //Sphere esf2 = Sphere(Point3(1.0, 0.0, -1.5), 0.5, m2);
    //Sphere esf3 = Sphere(Point3(2.0, 1.5, -2.5), 1, m3);
    //Sphere esf4 = Sphere(Point3(4.0, 1.5, -7), 3, m2);
    //Cylinder cil1 = Cylinder(Point3(-2, 0, -3.0), 1.0f, 1.0f, Vector3(0, 1, -1.0), m3);
    //Cone cone1 = Cone(Point3(0, -3, -3.0), Vector3(0, 1.0, -1.0), 2.0, 1.0, m2);
    //MeshObject mesh = makeCube(-2, 2, -2.0, 2.0, 2.0, -2.0, m4, m3, m1, m2);
    // mesh.setMaterial(m4);



    Plane plane = Plane(Point3(0, -7, 0), Vector3(0, 1, 0), planeFloor);

    //casa
    MeshObject casaParede = makeCube(-2, 2, -2.0, 2.0, 2.0, -2.0, m4, m3, m1, m2);
    TriangleFace casaFrente = TriangleFace(Point3(-2, 2, 2), Point3(2,2,2), Point3(0,3,2), m4);
    TriangleFace casaTras = TriangleFace(Point3(-2, 2, -2), Point3(2,2,-2), Point3(0,3,-2), m4);
    MeshObject porta = makeRet(-0.5, 0.5, -2, 0, 2.000001, m3);
    MeshObject janela1 = makeRet(-1.5, -1, -0.5, 0.5, 2.000001, m3);
    MeshObject janela2 = makeRet(1, 1.5, -0.5, 0.5, 2.000001, m3);
    MeshObject telhadoEsquerda = makeCube(-2.35, -2, 2.0, 3.0, 2.15, -2.15, m3, m3, m3, m3);
    MeshObject telhadoDireita = makeCube(2, 2.35, 2.0, 3.0, 2.15, -2.15, m3, m3, m3, m3);
    Vector3 dir = Vector3(0,-2,0);
    telhadoDireita.meshTranslate(dir);
    telhadoEsquerda.meshTranslate(dir);
    Vector3 zAxis = Vector3(0,0,1);
    Vector3 xAxis = Vector3(1,0,0);
    telhadoEsquerda.meshShear(zAxis, xAxis, 2);
    telhadoDireita.meshShear(zAxis, xAxis, -2);
    Vector3 dir2 = Vector3(0,2,0);
    telhadoEsquerda.meshTranslate(dir2);
    telhadoDireita.meshTranslate(dir2);
    //arvore
    Cylinder tronco1 = Cylinder(Point3(4, -2, 4), 0.2, 3, Vector3(0, 1, 0), m1);
    Cone copa11 = Cone(Point3(4, 3, 4), Vector3(0, 1, 0), 3.0, 1.0, m2);
    Cone copa12 = Cone(Point3(4, 4, 4), Vector3(0, 1, 0), 3.0, 1.0, m2);

    //snowman
    Sphere snow1 = Sphere(Point3(-4, -2, 4), 0.8, m1);
    Sphere snow2 = Sphere(Point3(-4, -0.6, 4), 0.6, m1);
    Sphere snow3 = Sphere(Point3(-4, 0.4, 4), 0.4, m1);

    Sphere snowZoi1 = Sphere(Point3(-4.005, 0.45, 4), 0.1, m2);
    Cone snowNose = Cone(Point3(-4, 0.4, 4.8), Vector3(0, 0, 1), 0.5, 0.1, m3);



    Cylinder xAx = Cylinder(Point3(0, 0, 0), 0.02, 10, Vector3(1, 0, 0), m3);
    Cylinder yAx = Cylinder(Point3(0, 0, 0), 0.02, 10, Vector3(0, 1, 0), m3);
    Cylinder zAx = Cylinder(Point3(0, 0, 0), 0.02, 10, Vector3(0, 0, 1), m3);

    Vector3 trVector = Vector3(4, 4, -5);
    //Vector3 goBack = trVector.reverse();
    Vector3 XZ_AXIS = Vector3(0, 0, 1);

    //mesh.meshTranslate(trVector);
    //trVector = Vector3(1, 0, 0);
    //mesh.meshShear(XZ_AXIS, trVector, 1);

    // mesh.meshScale(trVector, mesh.mesh[0].v1);
    // mesh.meshRotate(X_AXIS, 1.0);
    // mesh.meshTranslate(goBack);

    // trVector = Vector3(1, 0, 0);
    // cone1.rotate(trVector, 5);
    
    // objects.push_back(&esf1);
    // objects.push_back(&esf2);
    // objects.push_back(&esf3);
    // objects.push_back(&esf4);
    //objects.push_back(&cil1);
    //objects.push_back(&cone1);
    //objects.push_back(&mesh);
    objects.push_back(&tronco1);
    objects.push_back(&copa11);
    objects.push_back(&copa12);
    objects.push_back(&snow1);
    objects.push_back(&snow2);
    objects.push_back(&snow3);
    objects.push_back(&snowZoi1);
    objects.push_back(&snowNose);
    // objects.push_back(&yAx);
    // objects.push_back(&zAx);
    objects.push_back(&plane);
    objects.push_back(&casaParede);
    objects.push_back(&casaFrente);
    objects.push_back(&casaTras);
    objects.push_back(&porta);
    objects.push_back(&janela1);
    objects.push_back(&janela2);
    objects.push_back(&telhadoEsquerda);
    objects.push_back(&telhadoDireita);


    int o = objects.size();

    AmbientLight ambientLight = AmbientLight(0.1);

    PointLight pointLight = PointLight(Point3(-10, 10, 10), reflectionFromRGB(255, 255, 255), reflectionFromRGB(255, 255, 255));

    vector<Light*> lights = {
        &ambientLight,
        &pointLight
    };

    // ===== WORLD COORDINATES TO CAMERA COORDINATES TRANSFORMATION =======

    for (int i = 0; i < lights.size(); i++) {
        lights[i]->toCamera(camera.worldToCamera);
    }

    for (int i = 0; i < objects.size(); i++) {
        objects[i]->toCamera(camera.worldToCamera);
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
                objects[e]->intercepts(raio, interception);
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
    render();
}