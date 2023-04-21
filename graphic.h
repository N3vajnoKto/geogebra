#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QVBoxLayout>
#include <QDebug>
#include <QLine>
#include <QColor>
#include <QWheelEvent>

struct Point {
    const long double scale = 1.1;
    const long double defaultStep = 70;

    long double x;
    long double y;
    long double step = defaultStep;
    long double numberStep = 1;
    int changeNumber = 0;
    int signNumber = 1;

    void setPoint(long double, long double);
};

class Graphic : public QWidget {
    Q_OBJECT

public:
    Graphic();
    ~Graphic();
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void wheelEvent(QWheelEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void leaveEvent(QMouseEvent*);
    QString getNumber(long double, int);

public slots:
    void draw();

private:
    QTimer* timer = nullptr;
};

#endif // GRAPHIC_H
