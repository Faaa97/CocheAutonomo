#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //opciones(new Ui::MainWindow);
    //opciones->setupUi(this);
    ui->setupUi(this);

    //connect(actionOpciones, SIGNAL(click()), this, SLOT(on_actionOpciones_triggered()));

    gridSize = 30;
    gridPoints.setX(10);
    gridPoints.setY(10);
    inicioPoints.setX(1);
    inicioPoints.setY(1);
    finPoints.setX(10);
    finPoints.setY(10);
    obstaculosp = 0;
    obstaculosAleatorios = false;
    obstaculosDefinidos = false;

    obstaculosPoints.resize(gridPoints.getX()*gridPoints.getY());
    cochePoints = PairPoint();

    inicio = NULL;
    fin = NULL;

    setGrid();
    setInicio();
    setFin();
    //RefreshPoints();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ValueX_valueChanged(int arg1){
    gridPoints.setX(arg1);
    RefreshGrid();
}

void MainWindow::on_ValueY_valueChanged(int arg1){
    gridPoints.setY(arg1);
    RefreshGrid();
}
void MainWindow::setGrid(){
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    for(int i = 0; i < gridPoints.getX(); i++)
        for(int j = 0; j < gridPoints.getY(); j++)
            gridRectangles.push_back(scene->addRect(i*gridSize, j*gridSize, gridSize, gridSize, outlinePen, QBrush(Qt::white)));

    for(unsigned i = 0; i < gridRectangles.size(); i++)
        gridRectangles[i]->setZValue(GRIDZ);
}

void MainWindow::RefreshGrid(){
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    for(unsigned i = 0; i < gridRectangles.size(); i++)
        delete gridRectangles[i];

    gridRectangles.resize(0);

    for(int i = 0; i < gridPoints.getX(); i++)
        for(int j = 0; j < gridPoints.getY(); j++)
            gridRectangles.push_back(scene->addRect(i*gridSize, j*gridSize, gridSize, gridSize, outlinePen, QBrush(Qt::white)));

    for(unsigned i = 0; i < gridRectangles.size(); i++)
        gridRectangles[i]->setZValue(GRIDZ);
}

void MainWindow::setInicio(){
    if (inicio != NULL){
        delete inicio;
        inicio = NULL;
    }
    if( (inicioPoints.getX() > 0 && inicioPoints.getX() <= gridPoints.getX()) && (inicioPoints.getY() > 0 && inicioPoints.getY() <= gridPoints.getY()) )
        inicio = scene->addRect((inicioPoints.getX()-1)*gridSize, (inicioPoints.getY()-1)*gridSize, gridSize-1, gridSize-1, QPen(Qt::blue), QBrush(Qt::blue));
}

void MainWindow::setFin(){
    if (fin != NULL){
        delete fin;
        fin = NULL;
    }
    if( (finPoints.getX() > 0 && finPoints.getX() <= gridPoints.getX()) && (finPoints.getY() > 0 && finPoints.getY() <= gridPoints.getY()) )
        fin = scene->addRect((finPoints.getX()-1)*gridSize, (finPoints.getY()-1)*gridSize, gridSize-1, gridSize-1, QPen(Qt::red), QBrush(Qt::red));
}


void MainWindow::resizeEvent(QResizeEvent *){
    ui->graphicsView->setGeometry(0,0,this->width(),this->height()-gridSize);
}

void MainWindow::RefreshPoints(){

    if(obstaculosAleatorios && !obstaculosDefinidos){
        GenerarObstaculos();
        obstaculosDefinidos = true;
    }
    if(obstaculosDefinidos){

        for(unsigned i = 0; i < obstaculosPoints.size(); i++){

            if(obstaculosPoints[i].isDefined())
                obstaculos.push_back(scene->addRect(obstaculosPoints[i].getX()*gridSize,obstaculosPoints[i].getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::black), QBrush(Qt::black)));
        }
    }
    if(cochePoints.isDefined()){
        scene->addRect(cochePoints.getX()*gridSize,cochePoints.getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::green), QBrush(Qt::green));
    }

}

void MainWindow::GenerarObstaculos(){
    double numero = double(gridPoints.getX() * gridPoints.getY()) * double(obstaculosp)/100;
    int cont = 0;

    srand(time(NULL));

    do{
        int aux = (rand()*clock())% (gridPoints.getX()*gridPoints.getY());
        int ini = inicioPoints.getX() + inicioPoints.getY()*gridPoints.getX();
        int fi = finPoints.getX() + finPoints.getY()*gridPoints.getX();
        if(!obstaculosPoints[aux].isDefined() && aux != ini && aux != fi){
            obstaculosPoints[aux] = PairPoint(aux/gridPoints.getX(),aux%gridPoints.getX());
            cont++;
        }
    }while(cont < numero);


}

void MainWindow::on_ValueInicioX_valueChanged(int arg1)
{
    inicioPoints.setX(arg1);
    setInicio();
}

void MainWindow::on_ValueInicioY_valueChanged(int arg1)
{
    inicioPoints.setY(arg1);
    setInicio();
}

void MainWindow::on_ValueFinX_valueChanged(int arg1)
{
    finPoints.setX(arg1);
    setFin();
}

void MainWindow::on_ValueFinY_valueChanged(int arg1)
{
    finPoints.setY(arg1);
    setFin();
}

void MainWindow::on_ObstaculosAleatorios_toggled(bool checked)
{
    obstaculosAleatorios = checked;
}


void MainWindow::on_PorcentajeObstaculos_valueChanged(int arg1)
{
    obstaculosp = arg1;
    if(obstaculosAleatorios)
        RefreshPoints();
}

void MainWindow::on_actionOpciones_triggered()
{
    //opciones = new OpcionesWindow;
    //opciones->show();
}

void MainWindow::defineGridPoints(int x, int y){
    gridPoints.setX(x);
    gridPoints.setY(y);
}
void MainWindow::defineInicioPoints(int x, int y){
    inicioPoints.setX(x);
    inicioPoints.setY(y);
}
void MainWindow::defineFinPoints(int x, int y){
    finPoints.setX(x);
    finPoints.setY(y);
}
void MainWindow::defineObstaculosP(int o){
    obstaculosp = o;
}

void MainWindow::on_pushButton_released()
{
    simulacion();
}

void MainWindow::simulacion(){

    cochePoints = inicioPoints;
}
