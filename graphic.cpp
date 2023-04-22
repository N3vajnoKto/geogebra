#include "graphic.h"
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>

void Graphic::Point::setPoint(long double newWidth, long double newHeight) {
    x = newWidth;
    y = newHeight;
}

void Graphic::Point::setDefault(long double newWidth, long double newHeight) {
    x = newWidth;
    y = newHeight;
    step = defaultStep;
    numberStep = 1;
    changeNumber = 0;
    signNumber = 1;
}

Graphic::Graphic()
{
    resize(1000, 500);
    windowWidth = 1000;
    windowHeight = 500;

    point.setPoint(this->width() / 2, this->height() / 2);

    homeButton = new QPushButton(this);
    QIcon homeIcon("D:/Code QT/Graphic/Home.jpg");
    homeButton->setIcon(homeIcon);
    homeButton->setIconSize(QSize(40, 40));
    homeButton->setFixedSize(45, 45);
    homeButton->move(width() - homeButton->width() - 10, height() - homeButton->height() - 10);
    connect(homeButton, &QPushButton::clicked, this, &Graphic::returnHome);

    incButton = new QPushButton(this);
    QIcon incIcon("D:/Code QT/Graphic/Zoom in.jpg");
    incButton->setIcon(incIcon);
    incButton->setIconSize(QSize(35, 35));
    incButton->setFixedSize(45, 45);
    incButton->move(width() - incButton->width() - 10, height() - homeButton->height() - incButton->height() - 10);
    connect(incButton, &QPushButton::clicked, this, &Graphic::zoomIn);

    decButton = new QPushButton(this);
    QIcon decIcon("D:/Code QT/Graphic/Zoom out.jpg");
    decButton->setIcon(decIcon);
    decButton->setIconSize(QSize(35, 35));
    decButton->setFixedSize(45, 45);
    decButton->move(width() - decButton->width() - 10, height() - homeButton->height() - incButton->height() - decButton->height() - 10);
    connect(decButton, &QPushButton::clicked, this, &Graphic::zoomOut);

    setMouseTracking(true);
}

Graphic::~Graphic() {
    delete timer;
    delete homeButton;
    delete decButton;
    delete incButton;
}

void Graphic::resizeEvent(QResizeEvent*) {
    point.setPoint(point.x / windowWidth * this->width(), point.y / windowHeight * this->height());
    windowWidth = this->width();
    windowHeight = this->height();

    homeButton->move(width() - homeButton->width() - 10, height() - homeButton->height() - 10);
    incButton->move(width() - incButton->width() - 10, height() - homeButton->height() - incButton->height() - 10);
    decButton->move(width() - decButton->width() - 10, height() - homeButton->height() - incButton->height() - decButton->height() - 10);

    update();
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

    QFont font(painter.font());
    QString currentString;

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

    long double xPosition = 0;
    long double yPosition = 0;

    for (long double lineHeight = point.y - point.step, number = point.numberStep; lineHeight >= 0;
         lineHeight -= point.step, number += point.numberStep) {

        painter.setPen(gridDivision);
        painter.drawLine(0, lineHeight, this->width(), lineHeight);

        painter.setPen(Qt::black);
        QFontMetrics str(font);
        currentString = getNumber(number, point.signNumber);

        xPosition = std::max(static_cast<long double>(5),
                             point.x - str.horizontalAdvance(currentString) - 5);
        xPosition = std::min(xPosition, static_cast<long double>(this->width()) - 30);
        yPosition = lineHeight + 5;

        painter.drawText(xPosition, yPosition, currentString);
    }
    for (long double lineHeight = point.y + point.step, number = -point.numberStep;
         lineHeight < this->height(); lineHeight += point.step, number -= point.numberStep) {

        painter.setPen(gridDivision);
        painter.drawLine(0, lineHeight, this->width(), lineHeight);

        painter.setPen(Qt::black);
        QFontMetrics str(font);
        currentString = getNumber(number, point.signNumber);

        xPosition = std::max(static_cast<long double>(5),
                             point.x - str.horizontalAdvance(currentString) - 5);
        xPosition = std::min(xPosition, static_cast<long double>(this->width()) - 30);
        yPosition = lineHeight + 5;

        painter.drawText(xPosition, yPosition, currentString);
    }
    for (long double lineWidth = point.x - point.step, number = -point.numberStep; lineWidth >= 0;
         lineWidth -= point.step, number -= point.numberStep) {

        painter.setPen(gridDivision);
        painter.drawLine(lineWidth, 0, lineWidth, this->height());

        painter.setPen(Qt::black);
        QFontMetrics str(font);
        currentString = getNumber(number, point.signNumber);

        xPosition = lineWidth - str.horizontalAdvance(currentString) / 2;
        yPosition = std::max(static_cast<long double>(15), point.y + str.height());
        yPosition = std::min(yPosition, static_cast<long double>(this->height()) - 5);

        painter.drawText(xPosition, yPosition, currentString);
    }
    for (long double lineWidth = point.x + point.step, number = point.numberStep;
         lineWidth < this->width(); lineWidth += point.step, number += point.numberStep) {

        painter.setPen(gridDivision);
        painter.drawLine(lineWidth, 0, lineWidth, this->height());

        painter.setPen(Qt::black);
        QFontMetrics str(font);
        currentString = getNumber(number, point.signNumber);

        xPosition = lineWidth - str.horizontalAdvance(currentString) / 2;
        yPosition = std::max(static_cast<long double>(15), point.y + str.height());
        yPosition = std::min(yPosition, static_cast<long double>(this->height()) - 5);

        painter.drawText(xPosition, yPosition, currentString);
    }

    painter.setPen(Qt::black);

    painter.drawLine(0, point.y, this->width(), point.y);
    painter.drawLine(point.x, 0, point.x, this->height());

    painter.restore();
}

void Graphic::wheelEvent(QWheelEvent* event) {
    QPoint angle = event->angleDelta();
    point.step = (angle.y() > 0 ? point.step * point.scale : point.step / point.scale);

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
            if (i % 3 == 1) mul = 2.5;
            point.numberStep = (point.changeNumber > 0 ? point.numberStep * mul
                                                       : point.numberStep / mul);
            if (i % 3 == 0 && i != 0) point.signNumber++;
        }
    }

    if (point.changeNumber > 0) point.signNumber = 1;

    update();
}

void Graphic::mousePressEvent(QMouseEvent* event)
{
    if (!(event->button() == Qt::LeftButton)) {
        return;
    }
    setCursor(Qt::ClosedHandCursor);
    isFirstMove = true;

    update();
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

    update();
}

void Graphic::mouseReleaseEvent(QMouseEvent*)
{
    isFirstMove = false;
    unsetCursor();
    update();
}

void Graphic::leaveEvent(QMouseEvent* event) {
    mouseReleaseEvent(event);
    update();
}

void Graphic::returnHome() {
    point.setDefault(this->width() / 2, this->height() / 2);
    update();
}

void Graphic::zoomOut() {
    QWheelEvent* event = new QWheelEvent(QPointF(3, 3), QPointF(7, 7), QPoint(5, 5), QPoint(7, 7), 6, Qt::Orientation::Horizontal, Qt::MouseButton::AllButtons, Qt::NoModifier);
    wheelEvent(event);
    delete event;
    update();
}

void Graphic::zoomIn() {
    QWheelEvent* event = new QWheelEvent(QPointF(3, 3), QPointF(7, 7), QPoint(5, 5), QPoint(-7, -7), 6, Qt::Orientation::Horizontal, Qt::MouseButton::AllButtons, Qt::NoModifier);
    wheelEvent(event);
    delete event;
    update();
}
