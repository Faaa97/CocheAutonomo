#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsRectItem>
#include<QGraphicsView>
#include<QGraphicsScene>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
