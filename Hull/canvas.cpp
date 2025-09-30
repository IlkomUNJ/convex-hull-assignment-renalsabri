#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>

Canvas::Canvas(QWidget* parent) : QWidget(parent), showHull(false), iterations(0) {
    setMinimumSize(800, 600);
    setStyleSheet("background-color: white;");
}

int Canvas::cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void Canvas::computeConvexHull() {
    iterations = 0;

    if (points.size() < 3) {
        hull = points;
        return;
    }

    std::vector<Point> pts = points;

    int minIdx = 0;
    for (size_t i = 1; i < pts.size(); i++) {
        iterations++;
        if (pts[i].y > pts[minIdx].y ||
            (pts[i].y == pts[minIdx].y && pts[i].x < pts[minIdx].x)) {
            minIdx = i;
        }
    }
    std::swap(pts[0], pts[minIdx]);
    Point pivot = pts[0];

    std::sort(pts.begin() + 1, pts.end(), [&](const Point& a, const Point& b) {
        iterations++;
        int cp = cross(pivot, a, b);
        if (cp == 0) {
            int distA = (a.x - pivot.x) * (a.x - pivot.x) + (a.y - pivot.y) * (a.y - pivot.y);
            int distB = (b.x - pivot.x) * (b.x - pivot.x) + (b.y - pivot.y) * (b.y - pivot.y);
            return distA < distB;
        }
        return cp > 0;
    });

    hull.clear();
    for (const Point& pt : pts) {
        iterations++;
        while (hull.size() > 1 && cross(hull[hull.size()-2], hull[hull.size()-1], pt) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pt);
    }
}

void Canvas::addPoint(int x, int y) {
    points.push_back(Point(x, y));
    update();
}

void Canvas::clear() {
    points.clear();
    hull.clear();
    showHull = false;
    iterations = 0;
    update();
}

void Canvas::runConvexHull() {
    computeConvexHull();
    showHull = true;
    update();
}

void Canvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (showHull && hull.size() > 1) {
        painter.setPen(QPen(Qt::red, 2));
        for (size_t i = 0; i < hull.size(); i++) {
            const Point& p1 = hull[i];
            const Point& p2 = hull[(i + 1) % hull.size()];
            painter.drawLine(p1.x, p1.y, p2.x, p2.y);
        }
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::blue));
    for (const Point& p : points) {
        painter.drawEllipse(QPoint(p.x, p.y), 4, 4);
    }

    if (showHull) {
        painter.setBrush(QBrush(Qt::red));
        for (const Point& p : hull) {
            painter.drawEllipse(QPoint(p.x, p.y), 5, 5);
        }
    }

    if (showHull) {
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 14, QFont::Bold));
        painter.drawText(10, 25, QString("%1 iterations").arg(iterations));
    }
}

void Canvas::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && !showHull) {
        addPoint(event->pos().x(), event->pos().y());
    }
}
