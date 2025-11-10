#ifndef PIPEENTITY_H
#define PIPEENTITY_H

#include "CoreEntities.h"
#include <QList> // Используем QList для удобства в Qt-проекте

namespace Flap::Core {

struct PipeEntity {
    // Центральная позиция X
    double x; 
    // Y-координата верхнего края просвета
    double gapTopY;
    
    // Размеры труб (ширина и высота просвета - константы)

    int width;
    int gapHeight;

    PipeEntity(double x_pos, double gap_y, int w, int h)
        : x(x_pos), gapTopY(gap_y), width(w), gapHeight(h) {}

    // Возвращает прямоугольники для верхней и нижней трубы
    QList<Rectangle> getRects(int worldHeight) const {
        
        Rectangle topPipe {
            Vector2D(x, 0), 
            Vector2D((double)width, gapTopY)
        };

        Rectangle bottomPipe {
            Vector2D(x, gapTopY + gapHeight),
            Vector2D((double)width, (double)worldHeight - gapTopY - gapHeight)
        };
        

        return {topPipe, bottomPipe};
    }
    
    // Передвижение трубы

    void move(double speed) {
        x -= speed;
    }
};


} // namespace Flap::Core

#endif // PIPEENTITY_H
