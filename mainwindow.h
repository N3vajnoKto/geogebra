#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QHBoxLayout>
#include "sidebar.h"
#include "graphic.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Graphic* graph;
    Sidebar* sidebar;
    const double sbPart = 0.27;
    void resizeEvent(QResizeEvent *event);
public slots:
    void give();
    void upd();

};

#endif // MAINWINDOW_H
