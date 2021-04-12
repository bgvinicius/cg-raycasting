#include "../object.hpp"

#include "../objects/sphere.hpp"
#include "../objects/cylinder.hpp"
#include "../objects/cone.hpp"
#include "../objects/triangle.hpp"
#include "../objects/meshobject.hpp"
#include "../objects/plane.hpp"
#include "../lights/material.hpp"
#include "../lights/light.hpp"

void makeWorld(vector<Object*> &esfs, vector<Light*> &lights) {
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

    trVector = Vector3(-1, -1, 2);
    esf1.translate(trVector);
    
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

    AmbientLight ambientLight = AmbientLight(0.1);

    PointLight pointLight = PointLight(Point3(-10, 10, 10), reflectionFromRGB(255, 255, 255), reflectionFromRGB(255, 255, 255));

    lights.push_back(&ambientLight);
    lights.push_back(&pointLight);
}

vector<Object*> makeObjects() {

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

    trVector = Vector3(-1, -1, 2);
    esf1.translate(trVector);
    
    // esfs.push_back(&esf1);
    // esfs.push_back(&esf2);
    // esfs.push_back(&esf3);
    // esfs.push_back(&esf4);
    // esfs.push_back(&cil1);
    // esfs.push_back(&cone1);
    // esfs.push_back(&mesh);
    // // esfs.push_back(&xAx);
    // // esfs.push_back(&yAx);
    // // esfs.push_back(&zAx);
    // esfs.push_back(&plane);
    return vector<Object*> {
        &esf1,
        &esf2
    };
}