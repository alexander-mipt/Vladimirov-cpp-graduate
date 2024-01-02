//-----------------------------------------------------------------------------
//
// Source code for MIPT ILab
// Slides: https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
//  Bad code violating SRP: polygon does too much
//
//----------------------------------------------------------------------------
/*
    Класс зависит от реализации screen, bytestream, ...
    Класс зависит от структуры вектора
*/

#include <iostream>
#include <vector>

using Screen = std::ostream;
using ByteStream = std::ostream;

struct Vector3D {
    int x{0};
    int y{0};
    Vector3D &operator+=(const Vector3D &lhs) {
        x += lhs.x;
        y += lhs.y;
        return *this;
    }
};

struct Quaternion {
    Vector3D v{};
    int w{0};
};

void draw(Screen &s, Vector3D v) { s << "(" << v.x << ", " << v.y << ")"; }



class Polygon3D {
    std::vector<Vector3D> m_vs{};

  public:
    Polygon3D(std::initializer_list<Vector3D> il) : m_vs(il) {}
    void move(const Vector3D &t) {
        for (auto &v : m_vs)
            v += t;
    }
    void transpose(const Quaternion &q) {}
    void draw(Screen &s) const {
        for (auto v : m_vs) {
            ::draw(s, v);
            std::cout << "\n";
        }
    }
    void serialize(ByteStream &bs) const { draw(bs); }
};

int main() {
    Polygon3D p = {{2, 1}, {-3, 7}};
    p.draw(std::cout);
}