#ifndef OPCIONESWINDOW_H
#define OPCIONESWINDOW_H

#include <QDialog>
#include "pairpoint.hpp"

namespace Ui {
class OpcionesWindow;
}

class OpcionesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OpcionesWindow(QWidget *parent = 0);
    ~OpcionesWindow();

    PairPoint getGridPoints();
    PairPoint getInicioPoints();
    PairPoint getFinPoints();
    bool getObstaculosAleatorios();
    int getObstaculosPorcentaje();
    int getDelayTime();
    bool getMostrarVisitados();
    int getHeuristica();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_InicioX_valueChanged(int arg1);

    void on_InicioY_valueChanged(int arg1);

    void on_FinX_valueChanged(int arg1);

    void on_FinY_valueChanged(int arg1);

    void on_PorcentajeObstaculos_valueChanged(int arg1);

    void on_GridX_valueChanged(int arg1);

    void on_GridY_valueChanged(int arg1);

    void on_Velocidad_valueChanged(int arg1);

    void on_checkBox_toggled(bool checked);

    void on_Heuristic_currentIndexChanged(int index);

private:
    Ui::OpcionesWindow *ui;


    PairPoint gridPoints;
    PairPoint inicioPoints;
    PairPoint finPoints;
    int obstaculosPorcentaje;
    bool obstaculosAleatorios;
    int delayTime;
    bool mostrarVisitados;
    int heuristica;
};

#endif // OPCIONESWINDOW_H
