#include "sidebar.h"

Sidebar::Sidebar(QWidget *parent)
    : QWidget{parent}, area(new QScrollArea(this)), list(new QWidget(area)), button(new QPushButton(list))
{
    button->setFixedHeight(hLine);
    button->setFont(QFont("arial", 12));
    button->setIcon(QIcon(":/icons/plus.png"));
    button->setStyleSheet("QPushButton{background : white;"
                          "border : none; border-bottom : 1 solid rgb(200, 200, 200);}"
                          "QPushButton:hover{ transition: all 2s; background : rgb(250, 250, 250);"
                          "border : none; border-bottom : 1 solid rgb(200, 200, 200);}");

    QPalette palSide;
    palSide.setColor(QPalette::Window, Qt::white);
    area->setAutoFillBackground(true);
    area->setPalette(palSide);
    setAutoFillBackground(true);
    setPalette(palSide);
    QGridLayout* lay = new QGridLayout();
    lay->addWidget(area);
    lay->setSpacing(0);
    lay->setContentsMargins(QMargins(0,0,0,0));
    area->setFrameStyle(QFrame::NoFrame);
    setLayout(lay);
    area->setWidget(list);
    list->resize(width(), button->height() + 2 * margin);
    layList = new QVBoxLayout();
    layList->setContentsMargins(QMargins(margin,margin,margin,margin));
    layList->setSpacing(innerPadding);
    layList->addWidget(button);
    list->setLayout(layList);

    QPalette pal;
    pal.setColor(QPalette::Window, Qt::white);
    list->setAutoFillBackground(true);
    list->setPalette(pal);

    area->setStyleSheet("QScrollBar{width : 2; }");

    connect(button, &QPushButton::clicked, this, &Sidebar::addLine);

}

void Sidebar::resizeEvent(QResizeEvent *event) {
    list->resize(event->size().width() - padding, list->height());
}

void Sidebar::addLine() {
    auto line = new Equation(this);
    lines.insert(line);
    layList->addWidget(line);
    connect(line, &Equation::isDeleted, this, &Sidebar::removeLine);
    connect(line, &Equation::updGraph, this, &Sidebar::upd);
    list->resize(list->width(), list->height() + line->height() + innerPadding);
    emit req();
}

void Sidebar::removeLine(Equation* ref) {
    layList->removeWidget(ref);
    list->resize(list->width(), list->height() - ref->height() - innerPadding);
    lines.erase(ref);
    delete ref;
    upd();
    emit req();
}

void Sidebar::upd() {
    emit updGraph();
}
