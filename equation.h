#ifndef EQUATION_H
#define EQUATION_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <iostream>
#include <QColorDialog>
#include <random>
#include "colorbutton.h"

class Equation : public QFrame
{
    Q_OBJECT
public:
    explicit Equation(QWidget *parent = nullptr);
    QLineEdit* line;
    QPushButton* button;
    QString text();
    QColor color = Qt::green;
    ColorButton* colorButton;
private:

public slots:
    void del();
    void upd();
    void updColor();

signals:
    void isDeleted(Equation*);
    void updGraph();
};

#endif // EQUATION_H
