#include "opcioneswindow.h"
#include "ui_opcioneswindow.h"

OpcionesWindow::OpcionesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpcionesWindow)
{
    ui->setupUi(this);

    gridPoints = PairPoint(10,10);
    inicioPoints = PairPoint(0,0);
    finPoints = PairPoint(9,9);
    obstaculosAleatorios = true;
    obstaculosPorcentaje = 0;
    delayTime = 500;
    mostrarVisitados = true;
    heuristica = 0;
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

int OpcionesWindow::getDelayTime(){
    return delayTime;
}

bool OpcionesWindow::getMostrarVisitados(){
    return mostrarVisitados;
}

int OpcionesWindow::getHeuristica(){
   return heuristica;
}

void OpcionesWindow::on_buttonBox_accepted()
{
}

void OpcionesWindow::on_buttonBox_rejected()
{

}

void OpcionesWindow::on_InicioX_valueChanged(int arg1)
{
    inicioPoints.setX(arg1-1);
}

void OpcionesWindow::on_InicioY_valueChanged(int arg1)
{
    inicioPoints.setY(arg1-1);
}

void OpcionesWindow::on_FinX_valueChanged(int arg1)
{
    finPoints.setX(arg1-1);
}

void OpcionesWindow::on_FinY_valueChanged(int arg1)
{
    finPoints.setY(arg1-1);
}

void OpcionesWindow::on_PorcentajeObstaculos_valueChanged(int arg1)
{
    obstaculosPorcentaje = arg1;
    if(arg1 == -1){
        obstaculosAleatorios = false;
    }
}

void OpcionesWindow::on_GridX_valueChanged(int arg1)
{
    gridPoints.setX(arg1);
}

void OpcionesWindow::on_GridY_valueChanged(int arg1)
{
    gridPoints.setY(arg1);
}

void OpcionesWindow::on_Velocidad_valueChanged(int arg1)
{
    delayTime = arg1;
}

void OpcionesWindow::on_checkBox_toggled(bool checked)
{
    mostrarVisitados = checked;
}

void OpcionesWindow::on_Heuristic_currentIndexChanged(int index)
{
    heuristica = index;
}
