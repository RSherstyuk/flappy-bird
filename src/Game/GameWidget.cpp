#include "GameWidget.h"

#include "Constants.h"
#include <QPainter>

#include <QKeyEvent>
#include <QDebug>

// Размеры птицы (нужны только для рендеринга)
const double BIRD_RENDERING_WIDTH = 20.0;
const double BIRD_RENDERING_HEIGHT = 20.0;


GameWidget::GameWidget(QWidget *parent) // <-- QWidget
    : QWidget(parent)

{
    // Инициализация движка
    m_gameEngine = new Flap::Engine::GameEngine(WINDOW_WIDTH, WINDOW_HEIGHT, this);
    
    m_gameTimer = new QTimer(this);
    connect(m_gameTimer, &QTimer::timeout, this, &GameWidget::updateGame);
    m_gameTimer->start(GAME_TIMER_INTERVAL);
    
    // Важно для QWidget, чтобы ловить ввод с клавиатуры

    setFocusPolicy(Qt::StrongFocus);

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

GameWidget::~GameWidget() 
{
    // QWidget автоматически удалит QTimer и QObject-дочерний m_gameEngine
}

void GameWidget::drawRectangle(QPainter *painter, const Flap::Core::Rectangle& rect, const QColor& color)
{
    painter->setBrush(color);

    // Для QPainter можно использовать QRectF, но для ясности используем поля struct
    painter->drawRect(rect.position.x, rect.position.y, rect.size.x, rect.size.y);
}

void GameWidget::paintEvent(QPaintEvent *event) // <-- paintEvent
{
    Q_UNUSED(event);
    QPainter painter(this); // <-- Передаем 'this'

    // 1. Фон
    painter.fillRect(rect(), QColor(135, 206, 235));

    // 2. Трубы
    const auto& pipes = m_gameEngine->getPipes();
    for (const auto& pipe : pipes) {
        // Получаем прямоугольники для отрисовки
        QList<Flap::Core::Rectangle> rects = pipe.getRects(WINDOW_HEIGHT);
        
        // Рисуем верхнюю и нижнюю часть
        drawRectangle(&painter, rects[0], Qt::darkGreen);
        drawRectangle(&painter, rects[1], Qt::darkGreen);
    }

    // 3. Птица
    const auto& bird = m_gameEngine->getBird();
    
    Flap::Core::Rectangle birdRect {
        bird.position, 
        Flap::Core::Vector2D(BIRD_RENDERING_WIDTH, BIRD_RENDERING_HEIGHT)
    };
    
    drawRectangle(&painter, birdRect, bird.isAlive ? Qt::yellow : Qt::red);

    // 4. Счет и Статус
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 24, QFont::Bold));
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, QString::number(bird.score));

    if (!m_gameEngine->isRunning() && bird.isAlive) {
        painter.setFont(QFont("Arial", 20));
        painter.drawText(rect(), Qt::AlignCenter, "Press SPACE to Start");
    } else if (!m_gameEngine->isRunning() && !bird.isAlive) {
        painter.setFont(QFont("Arial", 20));
        painter.drawText(rect(), Qt::AlignCenter, 
                          QString("Game Over! Score: %1\nPress SPACE to Restart").arg(bird.score));
    }
}

void GameWidget::keyPressEvent(QKeyEvent *event) // <-- keyPressEvent
{
    if (event->key() == Qt::Key_Space) {
        if (!m_gameEngine->isRunning() && !m_gameEngine->getBird().isAlive) {
            // Если игра закончилась, перезапускаем
            m_gameEngine->reset();
        }
        m_gameEngine->flapBird();
    }
}

void GameWidget::updateGame()
{
    m_gameEngine->update(); // Обновляем чистый движок
    update();              // Запрашиваем перерисовку
}
