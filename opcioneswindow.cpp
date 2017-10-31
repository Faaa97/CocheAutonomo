#include "opcioneswindow.h"
#include "ui_opcioneswindow.h"

OpcionesWindow::OpcionesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpcionesWindow)
{
    ui->setupUi(this);

    gridPoints = PairPoint(10,10);
    inicioPoints = PairPoint(1,1);
    finPoints = PairPoint(10,10);
    obstaculosAleatorios = true;
    obstaculosPorcentaje = 0;
}

OpcionesWindow::~OpcionesWindow()
{
    delete ui;
}

PairPoint OpcionesWindow::getGridPoints(){
    return gridPoints;
}
PairPoint OpcionesWindow::getInicioPoints(){
    return inicioPoints;
}
PairPoint OpcionesWindow::getFinPoints(){
    return finPoints;
}
bool OpcionesWindow::getObstaculosAleatorios(){
    return obstaculosAleatorios;
}
int OpcionesWindow::getObstaculosPorcentaje(){
    return obstaculosPorcentaje;
}

void OpcionesWindow::on_buttonBox_accepted()
{
    emit SIGNAL(accepted());
}

void OpcionesWindow::on_buttonBox_rejected()
{

}

void OpcionesWindow::on_InicioX_valueChanged(int arg1)
{
    inicioPoints.setX(arg1);
}

void OpcionesWindow::on_InicioY_valueChanged(int arg1)
{
    inicioPoints.setY(arg1);
}

void OpcionesWindow::on_FinX_valueChanged(int arg1)
{
    finPoints.setX(arg1);
}

void OpcionesWindow::on_FinY_valueChanged(int arg1)
{
    finPoints.setY(arg1);
}

void OpcionesWindow::on_PorcentajeObstaculos_valueChanged(int arg1)
{
    obstaculosPorcentaje = arg1;
}

void OpcionesWindow::on_GridX_valueChanged(int arg1)
{
    gridPoints.setX(arg1);
}

void OpcionesWindow::on_GridY_valueChanged(int arg1)
{
    gridPoints.setY(arg1);
}
