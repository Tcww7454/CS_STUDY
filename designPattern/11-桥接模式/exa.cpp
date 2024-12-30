#include <iostream>
#include <memory>

// 抽象类：形状
class Shape {
public:
    virtual void draw() = 0;  // 纯虚函数，子类必须实现
    virtual ~Shape() = default;
};

// 具体类：矩形
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};

// 具体类：圆形
class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

// 抽象类：颜色
class Color {
public:
    virtual void fill() = 0;  // 纯虚函数，子类必须实现
    virtual ~Color() = default;
};

// 具体类：红色
class Red : public Color {
public:
    void fill() override {
        std::cout << "Filling with Red Color" << std::endl;
    }
};

// 具体类：蓝色
class Blue : public Color {
public:
    void fill() override {
        std::cout << "Filling with Blue Color" << std::endl;
    }
};

// 桥接类：结合了形状和颜色
class ColoredShape {
protected:
    std::shared_ptr<Shape> shape;
    std::shared_ptr<Color> color;

public:
    ColoredShape(std::shared_ptr<Shape> s, std::shared_ptr<Color> c) 
        : shape(s), color(c) {}

    virtual void draw() {
        shape->draw();
        color->fill();
    }
};

// 具体类：红色矩形
class RedRectangle : public ColoredShape {
public:
    RedRectangle(std::shared_ptr<Shape> s, std::shared_ptr<Color> c)
        : ColoredShape(s, c) {}

    void draw() override {
        std::cout << "Drawing Red Rectangle: ";
        ColoredShape::draw();
    }
};

// 具体类：蓝色圆形
class BlueCircle : public ColoredShape {
public:
    BlueCircle(std::shared_ptr<Shape> s, std::shared_ptr<Color> c)
        : ColoredShape(s, c) {}

    void draw() override {
        std::cout << "Drawing Blue Circle: ";
        ColoredShape::draw();
    }
};

int main() {
    // 创建形状对象
    std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>();
    std::shared_ptr<Shape> circle = std::make_shared<Circle>();

    // 创建颜色对象
    std::shared_ptr<Color> red = std::make_shared<Red>();
    std::shared_ptr<Color> blue = std::make_shared<Blue>();

    // 创建具体的颜色和形状组合对象
    RedRectangle redRectangle(rectangle, red);
    BlueCircle blueCircle(circle, blue);

    // 绘制图形
    redRectangle.draw();
    blueCircle.draw();

    return 0;
}
