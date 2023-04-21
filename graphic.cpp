#include "graphic.h"
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

Point point;
Point mousePosition;
bool isFirstMove = false;

void Point::setPoint(long double newWidth, long double newHeight) {
    x = newWidth;
    y = newHeight;
}

Graphic::Graphic()
{
    resize(1000, 500);

    point.setPoint(this->width() / 2, this->height() / 2);

    timer = new QTimer;

    connect(timer, &QTimer::timeout, this, &Graphic::draw);
    timer->start(1);

    setMouseTracking(true);
}

Graphic::~Graphic() {
}

void Graphic::resizeEvent(QResizeEvent*) {
    point.setPoint(this->width() / 2, this->height() / 2);
}

QString Graphic::getNumber(long double number, int sign) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(sign) << number;
    return QString::fromStdString(out.str());
}

void Graphic::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.save();

    QColor gridSubDivision(192, 192, 192, 100);
    painter.setPen(gridSubDivision);

    for (long double lineHeight = point.y - point.step / 5; lineHeight >= 0; lineHeight -= point.step / 5) {
        painter.drawLine(0, lineHeight, this->width(), lineHeight);
    }
    for (long double lineHeight = point.y + point.step / 5; lineHeight < this->height(); lineHeight += point.step / 5) {
        painter.drawLine(0, lineHeight, this->width(), lineHeight);
    }
    for (long double lineWidth = point.x - point.step / 5; lineWidth >= 0; lineWidth -= point.step / 5) {
        painter.drawLine(lineWidth, 0, lineWidth, this->height());
    }
    for (long double lineWidth = point.x + point.step / 5; lineWidth < this->width(); lineWidth += point.step / 5) {
        painter.drawLine(lineWidth, 0, lineWidth, this->height());
    }

    QColor gridDivision(185, 185, 185);

    for (long double lineHeight = point.y - point.step, number = point.numberStep; lineHeight >= 0; lineHeight -= point.step, number += point.numberStep) {
        painter.setPen(gridDivision);
        painter.drawLine(0, lineHeight, this->width(), lineHeight);

        painter.setPen(Qt::black);
        painter.drawText(point.x + 3, lineHeight + 5, getNumber(number, point.signNumber));
    }
    for (long double lineHeight = point.y + point.step, number = -point.numberStep; lineHeight < this->height(); lineHeight += point.step, number -= point.numberStep) {
        painter.setPen(gridDivision);
        painter.drawLine(0, lineHeight, this->width(), lineHeight);

        painter.setPen(Qt::black);
        painter.drawText(point.x + 3, lineHeight + 5, getNumber(number, point.signNumber));
    }
    for (long double lineWidth = point.x - point.step, number = -point.numberStep; lineWidth >= 0; lineWidth -= point.step, number -= point.numberStep) {
        painter.setPen(gridDivision);
        painter.drawLine(lineWidth, 0, lineWidth, this->height());

        painter.setPen(Qt::black);
        painter.drawText(lineWidth, point.y, getNumber(number, point.signNumber));
    }
    for (long double lineWidth = point.x + point.step, number = point.numberStep; lineWidth < this->width(); lineWidth += point.step, number += point.numberStep) {
        painter.setPen(gridDivision);
        painter.drawLine(lineWidth, 0, lineWidth, this->height());

        painter.setPen(Qt::black);
        painter.drawText(lineWidth, point.y, getNumber(number, point.signNumber));
    }

    painter.setPen(Qt::black);

    painter.drawLine(0, point.y, this->width(), point.y);
    painter.drawLine(point.x, 0, point.x, this->height());


    painter.restore();
}

void Graphic::wheelEvent(QWheelEvent* event) {
    QPoint angle = event->angleDelta();
    if (angle.y() > 0) {
        point.step *= point.scale;
    } else {
        point.step /= point.scale;
    }

    bool isRebuild = false;
    if (point.step > 2 * point.defaultStep)
    {
        point.step = point.defaultStep;
        isRebuild = true;
        point.changeNumber--;
    }
    if (point.step < point.defaultStep * 2 / 3) {
        point.step = point.defaultStep;
        isRebuild = true;
        point.changeNumber++;
    }

    if (isRebuild) {
        point.numberStep = 1;
        point.signNumber = 1;

        for (int i = 0; i < std::abs(point.changeNumber); i++) {
            double mul = 2;
            switch (i % 3) {
                case 0:
                    break;
                case 1:
                    mul = 2.5;
                    break;
                case 2:
                    mul = 2;
                    break;
            }


            if (point.changeNumber > 0) {
                point.numberStep *= mul;
            } else {
                point.numberStep /= mul;
            }
            if (i % 3 == 2) point.signNumber++;
        }
    }
    if (point.changeNumber > 0) point.signNumber = 1;
}

void Graphic::mousePressEvent(QMouseEvent* event)
{
    if (!(event->button() == Qt::LeftButton)) {
        return;
    }
    setCursor(Qt::ClosedHandCursor);
    isFirstMove = true;
}

void Graphic::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() == Qt::LeftButton)) {
        return;
    }
    if (isFirstMove) {
        isFirstMove = false;
        mousePosition.setPoint(event->pos().x(), event->pos().y());
    }

    point.x += event->pos().x() - mousePosition.x;
    point.y += event->pos().y() - mousePosition.y;
    mousePosition.setPoint(event->pos().x(), event->pos().y());
}

void Graphic::mouseReleaseEvent(QMouseEvent*)
{
    isFirstMove = false;
    unsetCursor();
}

void Graphic::leaveEvent(QMouseEvent* event) {
    mouseReleaseEvent(event);
}

void Graphic::draw() {
    update();
}
