#ifndef COREENTITIES_H
#define COREENTITIES_H

#include <cmath>

namespace Flap::Core {

// --- 1. Векторы и Геометрия ---

struct Vector2D {
    double x;
    double y;

    Vector2D(double x_val = 0.0, double y_val = 0.0)
        : x(x_val), y(y_val) {}
};


struct Rectangle {
    Vector2D position;
    Vector2D size;

    // Вспомогательные функции для легкого доступа
    double left() const { return position.x; }
    double right() const { return position.x + size.x; }
    double top() const { return position.y; }
    double bottom() const { return position.y + size.y; }

    bool intersects(const Rectangle &other) const
    {
        return left() < other.right() &&
               right() > other.left() &&
               top() < other.bottom() &&
               bottom() > other.top();
    }
};

// --- 2. Сущность Птицы ---

struct BirdEntity {

    Vector2D position;
    double velocity;
    bool isAlive;
    int score;

    double fitness;

    BirdEntity()

        : position(0, 0), velocity(0.0), isAlive(true), score(0), fitness(0.0) {}

    // Метод для получения области столкновения (Bounding Box)
    Rectangle getBoundingBox(double width, double height) const {
        return Rectangle{position, Vector2D(width, height)};
    }
    
    // Метод для "взмаха"
    void flap(double strength) {
        velocity = strength;
    }
};

} // namespace Flap::Core


#endif // COREENTITIES_H
