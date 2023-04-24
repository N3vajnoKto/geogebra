#pragma once
#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <vector>
#include <QScrollArea>
#include <QResizeEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <set>
#include <QGridLayout>
#include <qDebug>
#include "equation.h"

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);
    std::set<Equation*> lines;
private:
    QScrollArea* area;
    QWidget* list;
    QPushButton* button;
    QVBoxLayout* layList;
    void resizeEvent(QResizeEvent*);
    const int hLine = 40;
    const int padding = 3;
    const int innerPadding = 5;
    const int margin = 10;

public slots:
    void addLine();
    void removeLine(Equation*);
    void upd();

signals:
    void req();
    void updGraph();

};

#endif // SIDEBAR_H
