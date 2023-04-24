#include "equation.h"

std::mt19937 rnd(345646353);

Equation::Equation(QWidget *parent)
    : QFrame{parent}, line(new QLineEdit(this)), button(new QPushButton(this))
{

    setFixedHeight(40);
    color = QColor(rnd() % 256, rnd() % 256, rnd() % 256);
    colorButton = new ColorButton(color, this);
    colorButton->setFixedSize(height(), height());
    colorButton->setStyleSheet("ColorButton{background: white; border : none; "
                               "border-left : 1 solid rgb(200, 200, 200);}"
                               "ColorButton:hover{background: rgb(250, 250, 250); border : none; "
                               "border-left : 1 solid rgb(200, 200, 200);}");

    button->setFixedSize(height(), height());
    button->setFont(QFont("arial", 12));
    button->setIcon(QIcon(":/icons/close.png"));
    button->setStyleSheet("QPushButton{background : white;"
                          "border : none; border-right : 1 solid rgb(200, 200, 200);}"
                          "QPushButton:hover{ background : rgb(250, 250, 250);"
                          "border : none; border-right : 1 solid rgb(200, 200, 200);}");
    line->setFrame(0);
    line->setFont(QFont("arial", 12));
    line->setAlignment(Qt::AlignVCenter);
    line->setMaximumHeight(10000);
    line->setPlaceholderText("...");

    QHBoxLayout* lay = new QHBoxLayout();
    lay->setSpacing(0);
    lay->setContentsMargins(QMargins(0 ,0 ,0 ,0));
    lay->addWidget(button);
    lay->addWidget(line);
    lay->addWidget(colorButton);
    setLayout(lay);

    connect(button, &QPushButton::clicked, this, &Equation::del);
    connect(line, &QLineEdit::textEdited, this, &Equation::upd);
    connect(colorButton, &ColorButton::clicked, this, &Equation::updColor);
}

void Equation::del() {
    emit isDeleted(this);
}

QString Equation::text() {
    return line->text();
}

void Equation::upd() {
    emit updGraph();
}

void Equation::updColor() {
    QColorDialog* cd = new QColorDialog();
    QColor cl = cd->getColor(color);
    color = cl;
    QPalette pal = colorButton->color->palette();
    pal.setColor(QPalette::Window, cl);
    colorButton->color->setPalette(pal);
}

