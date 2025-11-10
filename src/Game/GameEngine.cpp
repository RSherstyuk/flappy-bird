#include "GameEngine.h"
#include "../Game/Constants.h" // Используем константы для настроек
#include <QRandomGenerator>

namespace Flap::Engine {

GameEngine::GameEngine(int width, int height, QObject *parent)
    : QObject(parent), m_worldWidth(width), m_worldHeight(height)
{
    reset();

}


void GameEngine::reset()
{
    m_isRunning = false;
    m_bird.isAlive = true;
    m_bird.score = 0;
    m_bird.velocity = 0.0;
    

    // Начальная позиция птицы
    m_bird.position = Flap::Core::Vector2D(BIRD_X_POSITION, m_worldHeight / 2.0 - BIRD_HEIGHT / 2.0);

    
    m_pipes.clear();
    m_pipeSpawnTimer = 0;

    
    // Создаем первую трубу
    createNewPipe();

}


void GameEngine::flapBird()
{
    if (!m_isRunning) {
        m_isRunning = true;
    }
    if (m_bird.isAlive) {
        m_bird.flap(FLAP_STRENGTH);
    }
}


void GameEngine::update()
{
    if (!m_isRunning || !m_bird.isAlive) {
        return;
    }

    applyPhysics();
    updatePipes();
    handleScore();
    

    if (checkCollision()) {
        m_bird.isAlive = false;

        m_isRunning = false;
    }
}

void GameEngine::applyPhysics()
{

    // Гравитация
    m_bird.velocity += GRAVITY;
    
    // Обновление позиции
    m_bird.position.y += m_bird.velocity;
}

void GameEngine::updatePipes()
{
    // Двигаем трубы
    for (int i = 0; i < m_pipes.size(); ++i) {
        m_pipes[i].move(PIPE_SPEED);
    }

    // Удаляем трубы, ушедшие за экран

    if (!m_pipes.isEmpty() && m_pipes.first().x + m_pipes.first().width < 0) {
        m_pipes.removeFirst();

    }

    // Создаем новые трубы
    m_pipeSpawnTimer += PIPE_SPEED;
    if (m_pipeSpawnTimer >= PIPE_SPACING) {
        createNewPipe();
        m_pipeSpawnTimer = 0;

    }
}

void GameEngine::createNewPipe()
{
    int minGapTop = 50;
    int maxGapTop = m_worldHeight - PIPE_GAP - 50;
    // Случайная Y-позиция верхнего края просвета
    int gapTopY = QRandomGenerator::global()->bounded(minGapTop, maxGapTop);

    m_pipes.append(Flap::Core::PipeEntity(
        m_worldWidth, 

        (double)gapTopY, 

        PIPE_WIDTH, 
        PIPE_GAP
    ));

}


void GameEngine::handleScore()

{
    // Проверка на получение очка (когда труба прошла птицу по X)
    if (!m_pipes.isEmpty()) {
        const auto& pipe = m_pipes.first();
        // Если правый край трубы пересек левый край птицы И это еще не засчитано
        if (pipe.x + pipe.width < m_bird.position.x && pipe.x + pipe.width + PIPE_SPEED >= m_bird.position.x) {
            m_bird.score++;
        }

    }
}

bool GameEngine::checkCollision()
{
    // 1. Столкновение с землей или потолком

    if (m_bird.position.y + BIRD_HEIGHT > m_worldHeight || m_bird.position.y < 0) {
        return true;
    }
    
    // Bounding box птицы
    const Flap::Core::Rectangle birdBox = m_bird.getBoundingBox(BIRD_WIDTH, BIRD_HEIGHT);

    // 2. Столкновение с трубами
    for (const auto& pipe : m_pipes) {
        // Получаем два прямоугольника (верх и низ) для текущей трубы
        QList<Flap::Core::Rectangle> pipeRects = pipe.getRects(m_worldHeight);

        
        for (const auto& rect : pipeRects) {

            if (birdBox.intersects(rect)) {
                return true;
            }
        }
    }
    
    return false;
}

} // namespace Flap::Engine
