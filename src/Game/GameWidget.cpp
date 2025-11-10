#include "GameWidget.h"

#include "Constants.h"
#include <QPainter>

#include <QDebug>
#include <QKeyEvent>
#include <QRandomGenerator>

GameWidget::GameWidget(QWidget *parent) : QWidget(parent) {
  setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  setFocusPolicy(Qt::StrongFocus);

  setupGame();
}

void GameWidget::setupGame() {
  m_gameTimer = new QTimer(this);

  connect(m_gameTimer, &QTimer::timeout, this, &GameWidget::updateGame);

  resetGame();
}

void GameWidget::resetGame() {
  m_gameRunning = false;
  m_score = 0;
  m_pipeSpawnTimer = 0;

  m_birdRect.setRect(BIRD_X_POSITION, WINDOW_HEIGHT / 2 - BIRD_SIZE / 2,
                     BIRD_SIZE, BIRD_SIZE);
  m_birdVelocity = 0;

  m_topPipes.clear();
  m_bottomPipes.clear();

  createPipe();

  m_gameTimer->start(GAME_TIMER_INTERVAL);

  update();
}

void GameWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);

  painter.fillRect(rect(), QColor(135, 206, 235)); // Sky blue

  painter.setBrush(Qt::green);
  for (const QRectF &pipe : m_topPipes) {
    painter.drawRect(pipe);
  }
  for (const QRectF &pipe : m_bottomPipes) {
    painter.drawRect(pipe);
  }

  painter.setBrush(Qt::yellow);
  painter.drawRect(m_birdRect);

  painter.setPen(Qt::black);
  painter.setFont(QFont("Arial", 24, QFont::Bold));
  painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter,
                   QString::number(m_score));

  if (!m_gameRunning) {
    painter.setFont(QFont("Arial", 20));
    painter.drawText(rect(), Qt::AlignCenter, "Press SPACE to Start");
  }
}

void GameWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Space) {
    if (!m_gameRunning) {
      resetGame();
      m_gameRunning = true;
    }

    m_birdVelocity = FLAP_STRENGTH;
  }
}

void GameWidget::updateGame() {
  if (!m_gameRunning) {
    return;
  }

  m_birdVelocity += GRAVITY;
  m_birdRect.translate(0, m_birdVelocity);

  bool scored = false;
  for (int i = 0; i < m_topPipes.size(); ++i) {
    m_topPipes[i].translate(-PIPE_SPEED, 0);
    m_bottomPipes[i].translate(-PIPE_SPEED, 0);

    if (m_topPipes[i].right() < m_birdRect.left() &&
        m_topPipes[i].right() + PIPE_SPEED >= m_birdRect.left()) {
      m_score++;
      scored = true;
    }
  }

  if (scored) {

    qDebug() << "Score:" << m_score;
  }

  if (!m_topPipes.isEmpty() && m_topPipes.first().right() < 0) {
    m_topPipes.removeFirst();
    m_bottomPipes.removeFirst();
  }

  m_pipeSpawnTimer += PIPE_SPEED;
  if (m_pipeSpawnTimer >= PIPE_SPACING) {
    createPipe();
    m_pipeSpawnTimer = 0;
  }

  if (checkCollision()) {
    m_gameRunning = false;
  }

  update();
}

void GameWidget::createPipe() {
  int minHeight = 50;
  int maxHeight = WINDOW_HEIGHT - PIPE_GAP - 50;
  int gapTop = QRandomGenerator::global()->bounded(minHeight, maxHeight);

  m_topPipes.append(QRectF(WINDOW_WIDTH, 0, PIPE_WIDTH, gapTop));

  m_bottomPipes.append(QRectF(WINDOW_WIDTH, gapTop + PIPE_GAP, PIPE_WIDTH,
                              WINDOW_HEIGHT - gapTop - PIPE_GAP));
}

bool GameWidget::checkCollision() {
  if (m_birdRect.bottom() > WINDOW_HEIGHT || m_birdRect.top() < 0) {
    return true;
  }

  for (const QRectF &pipe : m_topPipes) {
    if (m_birdRect.intersects(pipe)) {
      return true;
    }
  }
  for (const QRectF &pipe : m_bottomPipes) {
    if (m_birdRect.intersects(pipe)) {
      return true;
    }
  }

  return false;
}
