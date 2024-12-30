#include <iostream>

using namespace std;

// 目标接口
class Shape {
public:
    virtual void draw() = 0;  // 所有图形类都需要实现这个方法
    virtual ~Shape() = default;
};

// 外部库中的矩形类
class ExternalRectangle {
public:
    void drawRectangle() {
        std::cout << "Drawing rectangle using external library!" << std::endl;
    }
};

// 外部库中的圆形类
class ExternalCircle {
public:
    void drawCircle() {
        std::cout << "Drawing circle using external library!" << std::endl;
    }
};

// 矩形的适配器类
class RectangleAdapter : public Shape {
private:
    ExternalRectangle* externalRectangle;  // 外部库的矩形类实例

public:
    RectangleAdapter(ExternalRectangle* rectangle) : externalRectangle(rectangle) {}

    void draw() override {
        externalRectangle->drawRectangle();  // 调用外部库的方法
    }
};

// 圆形的适配器类
class CircleAdapter : public Shape {
private:
    ExternalCircle* externalCircle;  // 外部库的圆形类实例

public:
    CircleAdapter(ExternalCircle* circle) : externalCircle(circle) {}

    void draw() override {
        externalCircle->drawCircle();  // 调用外部库的方法
    }
};


int main() {
    // 创建外部库的矩形和圆形对象
    ExternalRectangle externalRectangle;
    ExternalCircle externalCircle;

    // 使用适配器将外部库的图形类适配为统一的Shape接口
    Shape* rectangle = new RectangleAdapter(&externalRectangle);
    Shape* circle = new CircleAdapter(&externalCircle);

    // 客户端通过统一的接口调用
    std::cout << "Client: ";
    rectangle->draw();  // 绘制矩形

    std::cout << "Client: ";
    circle->draw();  // 绘制圆形

    // 释放资源
    delete rectangle;
    delete circle;

    return 0;
}
