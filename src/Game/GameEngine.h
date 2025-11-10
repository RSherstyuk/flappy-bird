#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "CoreEntities.h"
#include "PipeEntity.h"
#include <QList>
#include <QObject> // Наследуемся от QObject, чтобы использовать QTimer

namespace Flap::Engine {

class GameEngine : public QObject
{
    Q_OBJECT

public:

    GameEngine(int width, int height, QObject *parent = nullptr);

    void reset();
    void update();
    void flapBird(); // Интерфейс для внешнего управления

    // Методы для доступа к состоянию
    const Flap::Core::BirdEntity& getBird() const { return m_bird; }
    const QList<Flap::Core::PipeEntity>& getPipes() const { return m_pipes; }
    bool isRunning() const { return m_isRunning; }

private:
    void applyPhysics();
    void updatePipes();
    void createNewPipe();
    bool checkCollision();
    void handleScore();

    // Размеры мира (окна)
    const int m_worldWidth;
    const int m_worldHeight;

    // Сущности
    Flap::Core::BirdEntity m_bird;
    QList<Flap::Core::PipeEntity> m_pipes;

    // Состояние
    bool m_isRunning;
    int m_pipeSpawnTimer;

    
    // Константы (для удобства)
    const double BIRD_WIDTH = 20.0;
    const double BIRD_HEIGHT = 20.0;
};

} // namespace Flap::Engine

#endif // GAMEENGINE_H
