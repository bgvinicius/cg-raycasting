#include <vector>

using namespace std;

class Matrix4 {
    public:
        vector<vector<float>> matrix { vector<float>{0, 0, 0, 0},  vector<float>{0, 0, 0, 0}, vector<float>{0, 0, 0, 0}, vector<float>{0, 0, 0, 0}};
};

Matrix4 identity() {
    // impl..
};

Matrix4 operator+(Matrix4 &u, Matrix4 &v) {
    
}

// -
// *

Matrix4 operator*(Matrix4 &m, float v) {
    // matriz vezes escalar
}

Matrix4 operator*(Matrix4 &m, Matrix4 &other) {
    // produtos entree matrizes
}