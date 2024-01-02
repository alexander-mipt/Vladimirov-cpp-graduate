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
    Добавим интерфейсы
*/
/*
    Проблема в том, что при добавлении отрисовки круга мы должны менять реализацию
*/

#include <iostream>
#include <vector>

using Screen = std::ostream;
using ByteStream = std::ostream;

struct IFigure {
    enum class Shape {
        VECTOR,
        POLYGON,
    };
    virtual Shape shape() const = 0;
    virtual ~IFigure() = default;
};

struct IScreen {
    virtual void draw(const IFigure &) = 0;
    virtual ~IScreen() = default;
};

class Screen : public IScreen {
  public:
    std::vector<const IFigure *> m_figures{};
    void draw(const IFigure &f) override {
        m_figures.push_back(&f);
    }
    void render() { /*for i in m_figures: shape() -> switch case: drawVector,
                       drawPolygon, ... */
        for (auto &&f : m_figures) {
            switch (f->shape()) {
            case IFigure::Shape::POLYGON:
                drawPolygon(*static_cast<const Polygon3D *>(f));
                break;
            case IFigure::Shape::VECTOR:
                drawVector(*static_cast<const Vector3D *>(f));
                break;
            default:
                break;
            }
        }
    }

  private:
    void drawVector(const Vector3D &v) const {
        std::cout << "vec{ " << v.x << ", " << v.y << "}";
    }
    void drawPolygon(const Polygon3D &poly) const {
        for (auto &&vec : poly) {
            drawVector(vec);
            std::cout << '\n';
        }
    }
};

std::ostream &operator<<(std::ostream &os, const Screen &scr) { return os; }

// std::ostream &operator<<(std::ostream &os, Screen &s) { return os; }

struct Vector3D : public IFigure {
    using Shape = IFigure::Shape;
    Vector3D() = default; // из-за наследования класс перестал быть агрегатом, и агрегатный вызов перестал работать
    Vector3D(int xp, int yp) : x(xp), y(yp) {}
    int x{0};
    int y{0};
    Vector3D &operator+=(const Vector3D &lhs) {
        x += lhs.x;
        y += lhs.y;
        return *this;
    }
    Shape shape() const override { return Shape::VECTOR; }
};

struct Quaternion {
    Vector3D v{};
    int w{0};
};

class Polygon3D : public IFigure {
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
    Shape shape() const override { return Shape::VECTOR; }

    CItt begin() const { return m_vs.cbegin(); }
    CItt end() const { return m_vs.cend(); }
};

int main() {
    Polygon3D p = {{2, 1}, {-3, 7}};
    // draw(p, std::cout);
}