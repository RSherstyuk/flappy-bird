#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget> // <-- Наследуемся от QWidget
#include <QTimer>

#include "GameEngine.h"

class GameWidget : public QWidget // <-- QWidget

{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr); // <-- QWidget

    ~GameWidget() override;

protected:
    // Возвращаемся к paintEvent и keyPressEvent
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame(); // Главный цикл

private:
    // Движок остается
    Flap::Engine::GameEngine *m_gameEngine;
    QTimer *m_gameTimer;
    
    // Вспомогательная функция для рисования (как раньше)
    void drawRectangle(QPainter *painter, const Flap::Core::Rectangle& rect, const QColor& color);
};

#endif // GAMEWIDGET_H
