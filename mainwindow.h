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
//#include <iostream>
#include <algorithm>    // std::sort
#include <QTime>
#include <QMessageBox>

const int GRIDZ = -1.0;
//const int INF = 9999;

namespace Ui {
class MainWindow;
//class OpcionesWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void opciones_accepted();

    void resizeEvent(QResizeEvent *);

    void on_actionOpciones_triggered();

    void on_actionSalir_triggered();

    void on_actionStart_triggered();

private:
    Ui::MainWindow *ui;
    OpcionesWindow *opciones;
    QGraphicsScene *scene;
    std::vector<QGraphicsRectItem*> gridRectangles;
    std::vector<PairPoint> gridNodes;
    QGraphicsRectItem* inicio;
    QGraphicsRectItem* fin;
    QGraphicsRectItem* coche;

    QMessageBox* warning;

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

    int delayTime;

private:

    void setGrid();
    void refreshGrid();

    void setInicio();
    void setFin();
    void setObstaculos();
    void setCoche();

    void GenerarObstaculos();

    int manhattanHeuristic(PairPoint node);
    int searchlowestfScore();
    std::list<PairPoint*> reconstructPath(PairPoint* current);
    void delay(int msec);
    void setVisitado();
};

#endif // MAINWINDOW_H
