#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Прямое объявление, чтобы не включать заголовок GameWidget
class GameWidget;

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  GameWidget *m_gameWidget; // Указатель на наш игровой виджет
};
#endif // MAINWINDOW_H
