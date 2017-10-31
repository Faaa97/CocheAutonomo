#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "pairpoint.hpp"
#include <time.h>
#include <cstdlib>
#include "opcioneswindow.h"
#include <set>
#include <list>
#include <iostream>

const int GRIDZ = -1.0;
//const int INF = 9999;

namespace Ui {
class MainWindow;
class OpcionesWindow;
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

    void on_ObstaculosAleatorios_toggled(bool checked);

    void resizeEvent(QResizeEvent *);

    void on_PorcentajeObstaculos_valueChanged(int arg1);

    void on_actionOpciones_triggered();

    void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    Ui::OpcionesWindow *opciones;
    QGraphicsScene *scene;
    std::vector<QGraphicsRectItem*> gridRectangles;
    std::vector<PairPoint> gridNodes;
    QGraphicsRectItem* inicio;
    QGraphicsRectItem* fin;
    QGraphicsRectItem* coche;

    std::vector<QGraphicsRectItem*> obstaculos;
    std::vector<PairPoint> obstaculosPoints;
    std::vector<PairPoint> visitadosPoints;

    int gridSize;
    PairPoint gridPoints;
    PairPoint inicioPoints;
    PairPoint finPoints;

    PairPoint cochePoints;

    int obstaculosp;
    bool obstaculosAleatorios;
    bool obstaculosDefinidos;

    std::list<PairPoint*> AStar();

    std::set<PairPoint*> closedSet;
    std::set<PairPoint*> openSet;

    std::vector<QGraphicsRectItem*> visitados;


public:
    void defineGridPoints(int x, int y);
    void defineInicioPoints(int x, int y);
    void defineFinPoints(int x, int y);
    void defineObstaculosP(int o);

private:

    void setGrid();
    void refreshGrid();

    void setInicio();
    void setFin();
    void setObstaculos();
    void setCoche();
    void setVisitado();

    void GenerarObstaculos();

    int manhattanHeuristic(PairPoint node);
    int searchlowestfScore();
    std::list<PairPoint*> reconstructPath(PairPoint* current);
    int searchCameFrom(PairPoint* node);

};

#endif // MAINWINDOW_H
