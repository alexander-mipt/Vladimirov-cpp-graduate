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
*/
/*
    Move draw outside the polygon --> iterators are needed
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

void draw(Screen &s, const Vector3D &v) {
    s << "(" << v.x << ", " << v.y << ")";
}
void draw(const Polygon3D &poly, Screen &s) {
    for (auto &&vec : poly) {
        draw(s, vec);
    }
    s << std::endl;
}

class Polygon3D {
    std::vector<Vector3D> m_vs{};
    using CItt = typename std::vector<Vector3D>::const_iterator;

  public:
    Polygon3D(std::initializer_list<Vector3D> il) : m_vs(il) {}
    void move(const Vector3D &t) {
        for (auto &v : m_vs)
            v += t;
    }
    void transpose(const Quaternion &q) {}
    // void serialize(ByteStream &bs) const { draw(bs); }

    CItt begin() const { return m_vs.cbegin(); }
    CItt end() const { return m_vs.cend(); }
};

int main() {
    Polygon3D p = {{2, 1}, {-3, 7}};
    draw(p, std::cout);
}