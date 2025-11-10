#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QList>
#include <QRectF>
#include <QTimer>
#include <QWidget>

class GameWidget : public QWidget {
  Q_OBJECT

public:
  GameWidget(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private slots:
  void updateGame();

private:
  void setupGame();
  void resetGame();
  void createPipe();
  bool checkCollision();

  QTimer *m_gameTimer;

  bool m_gameRunning;
  int m_score;

  QRectF m_birdRect;

  qreal m_birdVelocity;

  QList<QRectF> m_topPipes;
  QList<QRectF> m_bottomPipes;

  int m_pipeSpawnTimer;
};

#endif
