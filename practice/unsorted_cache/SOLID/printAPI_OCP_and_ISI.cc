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
    Проблема в том, что при добавлении отрисовки круга мы должны менять
   реализацию
*/
/*
 Теперь т.к. есть интерфейс IDrawable, мы можем добавить круг без изменений
 чего-либо в IScreen! Т.е. добавление отрисовки стало проще. Мы пришли к тому,
 что OpenClose principle привел нас к тому, что теперь нарушился single
 responsibility!!! OCP и SRP - противоречат друг другу. Как это поправить? Да
 никак, они противоречат друг другу. Но есть хак - шаблоны.

 Есть еще другая проблема: не надо в интерфейсе оставлять наследование.
 Контейнер полиморфных объектов должен быть с чистой value семанткой.

 Используем технику шаблонного наследника от общего шаблонного интерфейста.


*/

#include <iostream>
#include <vector>
#include <memory>

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
    // Shape shape() const override { return Shape::VECTOR; }

    CItt begin() const { return m_vs.cbegin(); }
    CItt end() const { return m_vs.cend(); }
};


struct IScreen {
    // virtual void draw(
    //     const IDrawable &) = 0; // here draw means push - typical design mistake
    // virtual void render() const = 0;
    // virtual std::ostream &stream() const = 0;
    virtual ~IScreen() = default;
};

class Screen : public IScreen {
  public:
    std::ostream& operator<<(const std::string str) {
        std::cout << str;
        return std::cout;
    }
  private:
};

void draw(int v, Screen &out, size_t position) {
    out << "int " << std::string(position, ' ') << "{" << v << "}\n";
}

void draw(Vector3D v, Screen &out, size_t position) {
    out << "vec " << std::string(position, ' ') << "{" << v.x << ", " << v.y << "}\n";
}

void draw(Polygon3D poly, Screen &out, size_t position) {
    out << "poly " << std::string(position, ' ') << "{\n";
    for (auto&& v: poly) {
        draw(v, out, position);
    }
    out << "}\n";
}

struct IDrawable {
    virtual void draw(const IScreen &s) const = 0; // here draw means draw
    virtual ~IDrawable() = default;
};


class Drawable {
    struct IDrawable {
        virtual ~IDrawable() = default;
        virtual std::unique_ptr<IDrawable> copy_() const = 0;
        virtual void draw_(Screen &, size_t) const = 0;
    };

    struct DrawableInt final : IDrawable {
        int m_data{};
        DrawableInt(int x) : m_data(std::move(x)) {}
        std::unique_ptr<IDrawable> copy_() const override {
            return std::make_unique<DrawableInt>(*this);
        }
        void draw_(Screen &out, size_t position) const override {
            ::draw(m_data, out, position);
        }
    };

    struct DrawableVector3D final : IDrawable {
        Vector3D m_data{};
        DrawableVector3D(Vector3D v) : m_data(std::move(v)) {}
        std::unique_ptr<IDrawable> copy_() const override {
            return std::make_unique<DrawableInt>(*this);
        }
        void draw_(Screen &out, size_t position) const override {
            ::draw(m_data, out, position);
        }
    };

    std::unique_ptr<IDrawable> m_self{};

    public:
    Drawable(int x) : m_self(std::make_unique<DrawableInt>(std::move(x))) {}
    Drawable(Vector3D v) : m_self(std::make_unique<DrawableVector3D>(std::move(v))) {}

    Drawable(const Drawable &x) : m_self(x.m_self->copy_()) {}
    Drawable (Drawable &&x) noexcept = default;
    Drawable &operator=(Drawable x) noexcept {
        m_self = std::move(x.m_self);
        return *this;
    }


};


int main() {
    Polygon3D p = {{2, 1}, {-3, 7}};
    // draw(p, std::cout);
}