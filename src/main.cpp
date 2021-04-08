#include <iostream>
#include "project/vector3.hpp"
#include "project/sphere.hpp"
#include <vector>
#include <math.h>
#include "project/camera.hpp"

using namespace std;

void write_color(std::ostream &out, float r, float g, float b) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(r) << ' '
        << static_cast<int>(g) << ' '
        << static_cast<int>(b) << '\n';
}

class TriangleFace {
    public:
        Point3 v1, v2, v3;
        Point3 rgb;

        TriangleFace(): v1(Point3(0, 0, 0)), v2(Point3(0, 0, 0)), v3(Point3(0, 0, 0)), rgb(Point3(0, 0, 0)) {

        }
        TriangleFace(Point3 v1, Point3 v2, Point3 v3, Point3 rgb): v1(v1), v2(v2), v3(v3), rgb(rgb) {}

        // void show() {
        //     cout << "v1: " << v1 << " v2: " << v2 << " v3: " << v3 << "\n";
        // }
};

float RayIntersectsTriangle(Ray &ray, 
                           TriangleFace &inTriangle)
{
    const float EPSILON = 0.0000001;
    Point3 vertex0 = inTriangle.v1;
    Point3 vertex1 = inTriangle.v2;  
    Point3 vertex2 = inTriangle.v3;
    float a,f,u,v;
    Vector3 edge1 = vertex1 - vertex0;
    Vector3 edge2 = vertex2 - vertex0;
    Vector3 h =  cross(ray.direction, edge2);// rayVector.crossProduct(edge2);
    a =  dot(edge1, h);// edge1.dotProduct(h);
    if (a > -EPSILON && a < EPSILON)
        return -1.0;    // This ray is parallel to this triangle.
    f = 1.0/a;
    Vector3 s = ray.origin - vertex0;// rayOrigin - vertex0;
    u = f * dot(s, h); // f * s.dotProduct(h);
    if (u < 0.0 || u > 1.0)
        return -1.0;
    Vector3 q = cross(s, edge1); //s.crossProduct(edge1);
    v = f * dot(ray.direction, q); //f * rayVector.dotProduct(q);
    if (v < 0.0 || u + v > 1.0)
        return -1.0;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * dot(edge2, q); //f * edge2.dotProduct(q);
    if (t > EPSILON) // ray intersection
    {
        // outIntersectionPoint = rayOrigin + rayVector * t;
        return t;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return -1.0;
}

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

bool doesIntercept(vector<Sphere> &esfs, int o, Ray &raio) {
    for (int e = 0; e < o; e++) {
        float interp = esfs[e].intersectColor(raio);

        if (interp >= 0) {
            return true;
        }
    }

    return false;
}

float computeLightingFloor(Vector3 &normal, Vector3 &pixelToEye, int s, Point3 &pontoInter, vector<Sphere> &esfs, int nesfs) {
    float i = 0.5;

    Vector3 lightD(0, 1, 0);

    Ray shadowRay = Ray(pontoInter, lightD);
    if (doesIntercept(esfs, nesfs, shadowRay)) {
        //cerr << "a";
        return i;
    }

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


float interceptsPlane(Ray &ray) {
    Point3 planePoint(0, -4, 0);
    Vector3 planeNormal(0, 1, 0);

    float numer = dot((planePoint - ray.origin), planeNormal);
    float den = dot(ray.direction, planeNormal);

    //return false;

    if (den == 0 || (numer / den) <= 1) {
        return -1.0;
    }

    return numer / den;
}

float interceptsCone(Ray &ray) {
    // cone center point
    Point3 C = Point3(0, 0, -3.0);
    // cone top point
    Point3 V = Point3(0, 0.0, -3.0);
    Vector3 n = unit_vector(Vector3(1.0, 0.0, 0));
    double H = 2.0;
    double R = 1.0;

    Point3 P0 = ray.origin;
    Vector3 d = ray.direction;

    Vector3 v = V - P0;

    double hipotenusa = sqrt(pow(H, 2.0) + pow(R, 2.0));
    double costeta = H / hipotenusa;
    double cos2teta = pow(costeta, 2.0);

    double a = pow(dot(d, n), 2.0) - (dot(d, d) * cos2teta);
    double b = (dot(v, d) * cos2teta) - (dot(v, n) * dot(d, n));
    double c = pow(dot(v, n), 2.0) - (dot(v, v)*cos2teta);

    double discriminant = b*b -a*c;

    if (discriminant <= 0) {
        return -1.0;
    }

    if (a == 0) {
        cerr << "a = 0";
    }

    auto t1 = (-1.0*b + sqrt(discriminant)) / (a);
    auto t2 = (-1.0*b - sqrt(discriminant)) / (a);

    if (t1 < 0 and t2 < 0) {
        return -1.0;
    }

    Point3 p1 = ray.pointAt(t1);
    Point3 p2 = ray.pointAt(t2);

    Vector3 vt1 = V - p1;
    Vector3 vt2 = V - p2;

    float h1 = dot(vt1, n);
    float h2 = dot(vt2, n);

    if ((h1 >= 0) and (h1 <= H)) {
        return 1.0;
    }

    if ((h2 >= 0) and (h2 <= H)) {
        return 1.0;
    }
    //cerr << "t1 " << t1 << " t2 " << t2 <<"\n ";
    return -1.0;
}

float interceptsCylinder(Ray &ray) {
    // cylinder base point
    Point3 B = Point3(0, 1, -3);

    // cylinder direction vector -- unit vector
    Vector3 u = unit_vector(Vector3(1, 1, 1));

    // cylinder height and radius
    float H = 1.0;
    float R = 1.0;

    // == auxiliary vectors to simplify the interception equation ==
    
    // ray direction
    Vector3 d = ray.direction;

    // ray origin
    Point3 P_0 = ray.origin;

    // v = (P0 - B) - ((P0 - B) dot u) * u
    Vector3 v = (P_0 - B) - ((dot(P_0 - B, u) * u)); 

    // w = d - (d dot u)*u
    Vector3 w = d - ((dot(d, u)) * u);

    // == quadratic equation ==

    float a = dot(w, w);
    float b = dot(v, w);
    float c = dot(v, v) - pow(R, 2);

    float discriminant = pow(b, 2) - (a*c);

    if (discriminant < 0) return -1.0;

    float t1 = (-b + sqrt(discriminant)) / a;
    float t2 = (-b - sqrt(discriminant)) / a;

    Point3 p1 = ray.pointAt(t1);
    Point3 p2 = ray.pointAt(t2);

    float h1 = dot(p1 - B, u);
    float h2 = dot(p2 - B, u);

    if (h1 >= 0 and h1 <= H) {
        return 1.0;
    }

    
    if (h2 >= 0 and h2 <= H) {
        return 1.0;
    }

    return -1.0;
}

int interceptTriangles(Ray &ray, vector<TriangleFace> &triangles) {
    int n = triangles.size();

    bool has = false;
    float nearestT = 10000;
    int winner = -1;
    for (int i = 0; i < n; i++) {
        float t = RayIntersectsTriangle(ray, triangles[i]);

        if (t > 0) {
            has = true;
            if (t < nearestT) {
                winner = i;
                nearestT = t;
            }
        }
    }

    if (has) {
        return winner;
    }

    return -1;
}

void render(vector<TriangleFace> &triangles) {
    Point3 eye = Point3(22, 5, -8);
    Point3 at = Point3(16, 0, -11);
    Point3 up = Point3(16, 1, -11);

    Camera c = Camera(eye, at, up);

    int cube_xmin = 14;
    int cube_xmax = 20;
    int cube_ymin = 0;
    int cube_ymax = 4;
    int cube_zmin = -11;
    int cube_zmax = -15;

    vector<TriangleFace> tr = {
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmin), Point3(1, 1, 211)), // frente
        TriangleFace(Point3(cube_xmin, cube_ymax, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymax, cube_zmin), Point3(1, 1, 211)), // frente
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmax), Point3(cube_xmin, cube_ymin, cube_zmax), Point3(111, 51, 1)), // lado esquerdo
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmin), Point3(cube_xmin, cube_ymax, cube_zmax), Point3(111, 51, 1)), // esq
        TriangleFace(Point3(cube_xmax, cube_ymin, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmin), Point3(211, 1, 1)), // dir
        TriangleFace(Point3(cube_xmax, cube_ymax, cube_zmin), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmax), Point3(211, 1, 1)), // dir
        TriangleFace(Point3(cube_xmin, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmin, cube_ymax, cube_zmax), Point3(211, 211, 211)), // tras
        TriangleFace(Point3(cube_xmin, cube_ymax, cube_zmax), Point3(cube_xmax, cube_ymin, cube_zmax), Point3(cube_xmax, cube_ymax, cube_zmax), Point3(211, 211, 211)), // tras
    };

    vector<TriangleFace> newFaces = {};

    for (int i =0; i < tr.size(); i++) {
        TriangleFace f = tr[i];

        TriangleFace f2 = TriangleFace();

        f2.v1 = c.worldToCamera * f.v1;
        f2.v2 = c.worldToCamera * f.v2;
        f2.v3 = c.worldToCamera * f.v3;
        f2.rgb.x = f.rgb.x;
        f2.rgb.y = f.rgb.y;
        f2.rgb.z = f.rgb.z;

        newFaces.push_back(f2);
    }

    eye = Point3(0, 0, 0);

    //eye = Point3(0, 0, 0);

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

    std::cerr << "renderizando...\n";

    vector<Sphere> esfs;

    vector<int> color {100, 150, 200, 30};
    vector<int> shine {10, 30, 40, 50};

    esfs.push_back(Sphere(Point3(0.0, 0.0, -2.0), 0.5));
    esfs.push_back(Sphere(Point3(1.0, 0.0, -2.5), 0.5));
    esfs.push_back(Sphere(Point3(2.0, 1.5, -3.5), 1));
    esfs.push_back(Sphere(Point3(4.0, 1.5, -8), 3));

    int o = 0;

    for (int h = height, i = 0; h >= 0; h--, i++) {
        for (int w = 0; w < width; w++) {
            // w anda dentro duma linha, i passa linha de cima pra baixo
            float x_pos = x_min + (delt_x / 2.0) + (w * delt_x);
            float y_pos = y_max - (delt_y / 2.0) - (i * delt_y);
            float z_pos = -1.0;

            // raio saindo da camera (eye) indo ate o centro do pixel no canvas
            //Vector3 direction(x_pos, y_pos, z_pos);

            Point3 pix = Point3(x_pos, y_pos, z_pos);
            Vector3 direction = pix - eye;

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
                float coneinter = interceptsCone(raio);
                //cerr << coneinter << "\n";
                int triangulopegue = interceptTriangles(raio, newFaces);
                if (triangulopegue != -1) {
                    TriangleFace f = newFaces[triangulopegue];
                    //cerr << triangulopegue;

                    write_color(std::cout, f.rgb.x, f.rgb.y, f.rgb.z);
                } else {
                    float interceptPos = interceptsPlane(raio);
                    if (interceptPos >= 0) {
                        Point3 p = raio.pointAt(interceptPos);
                        Vector3 inter = Vector3(0, 1, 0);
                        //Vector3 interToEye = direction.reverse();
                        Vector3 b = direction * -1;
                        float light = computeLightingFloor(inter, b, 3, p, esfs, o);

                        write_color(std::cout, 143, 103, 73);
                    } else {
                        write_color(std::cout, 255, 255, 255);
                    }
                }
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


    for (int i = 0; i < 12; i++) {
        string v;

        int p1, p2, p3;

        cin >> v >> p1 >> p2 >> p3;

        Point3 v1 = mycube[p1-1];
        Point3 v2 = mycube[p2-1];
        Point3 v3 = mycube[p3-1];

        TriangleFace face;

        face.v1 = v1;
        face.v2 = v2;
        face.v3 = v3;

        mycubefaces.push_back(face);
    }

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