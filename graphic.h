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
#include <QPushButton>

class Graphic : public QWidget {
    Q_OBJECT

public:

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
        void setDefault(long double, long double);
    };

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
    void returnHome();
    void zoomIn();
    void zoomOut();

private:
    QTimer* timer = nullptr;
    Point point;
    Point mousePosition;
    bool isFirstMove = false;
    double windowWidth;
    double windowHeight;
    QPushButton* decButton = nullptr;
    QPushButton* incButton = nullptr;
    QPushButton* homeButton = nullptr;
};

#endif // GRAPHIC_H
