#include "MainWindow.h"

#include "Constants.h"
#include "GameWidget.h"

MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent) {
  m_gameWidget = new GameWidget(this);

  setCentralWidget(m_gameWidget);

  setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

  setWindowTitle("Flappy Bird Qt");
}

MainWindow::~MainWindow() {}
