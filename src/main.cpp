#include <iostream>
#include "project/vector3.hpp"
#include "project/sphere.hpp"
#include <vector>
#include <math.h>

using namespace std;

void write_color(std::ostream &out, float r, float g, float b) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(r) << ' '
        << static_cast<int>(g) << ' '
        << static_cast<int>(b) << '\n';
}

float computeLighting(Vector3 &normal, Vector3 &pixelToEye, int s) {
    float i = 0.5;

    Vector3 lightD(0, 0, 1);
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

bool interceptsPlane(Ray &ray) {
    Point3 planePoint(0, -4, 0);
    Vector3 planeNormal(0, 1, 0);

    float numer = dot((planePoint - ray.origin), planeNormal);
    float den = dot(ray.direction, planeNormal);

    //return false;

    if (den == 0 || (numer / den) <= 0) {
        return false;
    }

    Point3 interpoint = ray.pointAt(numer / den);
    Vector3 test = interpoint - planePoint;
    return dot(test, planeNormal) == 0;
}

int main() {
    const auto eye = Point3(0, 0, 0);

    // const auto canvas_top_left = Point3(0, 2, -1);
    // const auto canvas_top_right = Point3(2, 2, -1);
    // const auto canvas_bottom_left = Point3(0, 0, -1);
    // const auto canvas_bottom_right = Point3(2, 0, -1);

    const int width = 800;
    const int height = 800;

    std::cout << "P3\n" << width << " " << height << "\n255\n";


    float x_max = 4.0;
    float x_min = -4.0;
    float y_min = -4.0;
    float y_max = 4.0;

    float delt_x = ((x_max - x_min) / width);
    float delt_y = ((y_max - y_min) / height);

    std::cerr << "renderizando";

    vector<Sphere> esfs;

    vector<int> color {100, 150, 200, 30};
    vector<int> shine {10, 30, 40, 50};

    esfs.push_back(Sphere(Point3(0.0, 0.0, -1.0), 0.5));
    esfs.push_back(Sphere(Point3(1.0, 0.0, -1.5), 0.5));
    esfs.push_back(Sphere(Point3(2.0, 1.5, -2.5), 1));
    esfs.push_back(Sphere(Point3(4.0, 1.5, -7), 3));

    int o = 4;

    for (int h = height, i = 0; h >= 0; h--, i++) {
        for (int w = 0; w < width; w++) {
            // w anda dentro duma linha, i passa linha de cima pra baixo
            float x_pos = x_min + (delt_x / 2.0) + (w * delt_x);
            float y_pos = y_max - (delt_y / 2.0) - (i * delt_y);
            float z_pos = -1.0;

            // raio saindo da camera (eye) indo ate o centro do pixel no canvas
            Vector3 direction(x_pos, y_pos, z_pos);
            Ray raio(eye, direction);

            bool didIntersect = false;
            for (int e = 0; e < o; e++) {
                float interp = esfs[e].intersectColor(raio);

                if (interp >= 0) {
                    Point3 p = raio.pointAt(interp);

                    Vector3 inter = unit_vector(p - esfs[e].center);
                    //Vector3 interToEye = direction.reverse();
                    Vector3 b = direction * -1;
                    float light = computeLighting(inter, b, shine[e]);

                    write_color(std::cout, e * 80 * light, e * 50 * light, color[e] * light);
                    didIntersect = true;
                    break;
                }
            }

            if (!didIntersect) {
                write_color(std::cout, 255, 255, 255);
                // if (interceptsPlane(raio)) {
                //     write_color(std::cout, 0, 200, 100);
                // } else {
                //     write_color(std::cout, 255, 255, 255);
                // }
            }
        }
    }
}