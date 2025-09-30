#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include "point.h"


class Canvas : public QWidget {
    Q_OBJECT

private:
    std::vector<Point> points;
    std::vector<Point> hull;
    bool showHull;
    int iterations;

    int cross(const Point& O, const Point& A, const Point& B);
    void computeConvexHull();

public:
    explicit Canvas(QWidget* parent = nullptr);
    void addPoint(int x, int y);

public slots:
    void clear();
    void runConvexHull();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
};

#endif
