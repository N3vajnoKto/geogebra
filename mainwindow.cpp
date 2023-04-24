#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sidebar(new Sidebar(this)), graph(new Graphic(this))
{
    resize(1000, 700);
    sidebar->resize(300, height());
    graph->resize(width() - sidebar->width(), height());
    connect(sidebar, &Sidebar::req, this, &MainWindow::give);
    connect(sidebar, &Sidebar::updGraph, this, &MainWindow::upd);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    sidebar->move(0,0);
    sidebar->resize(std::max(int(sbPart * 1000), int(sbPart * event->size().width())), height());
    graph->move(sidebar->width(), 0);
    graph->resize(width() - sidebar->width(), height());
}

MainWindow::~MainWindow()
{
}

void MainWindow::give() {
    graph->lines = &sidebar->lines;
}

void MainWindow::upd() {
    graph->update();
}

