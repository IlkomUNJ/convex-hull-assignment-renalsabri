#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Canvas;
class QPushButton;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Canvas* canvas;
    QPushButton* runButton;
    QPushButton* clearButton;

public:
    explicit MainWindow(QWidget* parent = nullptr);
};

#endif
