#include "mainwindow.h"
#include "canvas.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Convex Hull Visualizer");

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    canvas = new Canvas(this);
    mainLayout->addWidget(canvas);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    runButton = new QPushButton("Run Convex Hull", this);
    clearButton = new QPushButton("Clear", this);

    runButton->setStyleSheet("padding: 10px; font-size: 14px;");
    clearButton->setStyleSheet("padding: 10px; font-size: 14px;");

    buttonLayout->addWidget(runButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);

    connect(runButton, &QPushButton::clicked, canvas, &Canvas::runConvexHull);
    connect(clearButton, &QPushButton::clicked, canvas, &Canvas::clear);

    resize(820, 700);
}
