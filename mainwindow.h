#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "pairpoint.hpp"
#include "myqgraphicsview.h"
#include <time.h>
#include <cstdlib>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ValueX_valueChanged(int arg1);

    void on_ValueY_valueChanged(int arg1);

    void on_ValueInicioX_valueChanged(int arg1);

    void on_ValueInicioY_valueChanged(int arg1);

    void on_ValueFinX_valueChanged(int arg1);

    void on_ValueFinY_valueChanged(int arg1);

    void on_SliderObstaculos_valueChanged(int value);

    void on_ObstaculosAleatorios_toggled(bool checked);

    void resizeEvent(QResizeEvent *);

    void on_PorcentajeObstaculos_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::vector<QGraphicsRectItem*> rectangles;
    QGraphicsRectItem* inicio;
    QGraphicsRectItem* fin;

    std::vector<QGraphicsRectItem*> obstaculos;
    std::vector<PairPoint> obstaculosPoints;


    int gridSize;
    PairPoint gridPoints;
    PairPoint inicioPoints;
    PairPoint finPoints;

    int obstaculosp;
    bool obstaculosAleatorios;
    bool obstaculosDefinidos;


    void RefreshGrid(bool hard_reset = true);
    void RefreshPoints();
    void GenerarObstaculos();

    //void ObstacleCount();

};

#endif // MAINWINDOW_H
