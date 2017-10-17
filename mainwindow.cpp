#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    RefreshGrid();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ValueX_valueChanged(int arg1){
    gridPoints.setX(arg1);
    scene->clear();
    RefreshGrid();
}

void MainWindow::on_ValueY_valueChanged(int arg1){
    gridPoints.setY(arg1);
    scene->clear();
    RefreshGrid();
}

void MainWindow::RefreshGrid(bool hard_reset){
    scene = new QGraphicsScene(this);
    //int max =
    //ui->graphicsView->setGeometry(0,0,gridSize*(gridPoints.getX()+1),gridSize*(gridPoints.getY()+1));
    ui->graphicsView->setScene(scene);
    ui->groupBox->setStyleSheet("background-color:white;");
    //ui->groupBox->setGeometry(this->width()-5,ui->groupBox->height(),ui->groupBox->width(),ui->groupBox->height());
    //ui->graphicsView->resetMatrix();
    //ui->graphicsView->scale(1.5,1.5);
    //ui->graphicsView->fitInView();
    QBrush whiteBrush(Qt::white);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    for(int i = 0; i < gridPoints.getX(); i++){
        for(int j = 0; j < gridPoints.getY(); j++){
            rectangles.push_back(scene->addRect(i*gridSize, j*gridSize, gridSize, gridSize, outlinePen, whiteBrush));
        }
    }
    if(hard_reset == true){
        RefreshPoints();
    }
}

void MainWindow::resizeEvent(QResizeEvent *){
    ui->graphicsView->setGeometry(0,0,this->width(),this->height()-gridSize);
}

void MainWindow::RefreshPoints(){
    RefreshGrid(false);
    if( (inicioPoints.getX() > 0 && inicioPoints.getX() <= gridPoints.getX()) && (inicioPoints.getY() > 0 && inicioPoints.getY() <= gridPoints.getY()) )
        inicio = scene->addRect((inicioPoints.getX()-1)*gridSize, (inicioPoints.getY()-1)*gridSize, gridSize-1, gridSize-1, QPen(Qt::blue), QBrush(Qt::blue));

    if( (finPoints.getX() > 0 && finPoints.getX() <= gridPoints.getX()) && (finPoints.getY() > 0 && finPoints.getY() <= gridPoints.getY()) )
        fin = scene->addRect((finPoints.getX()-1)*gridSize, (finPoints.getY()-1)*gridSize, gridSize-1, gridSize-1, QPen(Qt::red), QBrush(Qt::red));

    if(obstaculosAleatorios && !obstaculosDefinidos){
        GenerarObstaculos();
        obstaculosDefinidos = true;
    }
    if(obstaculosDefinidos){
        printf("obstaculos.size = %d", obstaculos.size());
        for(int i = 0; i < obstaculosPoints.size(); i++){
            //printf("Estado: %d", obstaculosPoints[i].isDefined());
            if(obstaculosPoints[i].isDefined())
                obstaculos.push_back(scene->addRect(obstaculosPoints[i].getX()*gridSize,obstaculosPoints[i].getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::black), QBrush(Qt::black)));
        }
    }

}

void MainWindow::GenerarObstaculos(){
    double numero = double(gridPoints.getX() * gridPoints.getY()) * double(obstaculosp)/100;
    int cont = 0;
    printf("%f, %d\n", numero, obstaculosp);
    printf("%d : %d", gridPoints.getX(), gridPoints.getY());

    srand(time(NULL));

    do{
        int aux = (rand()*clock())% (gridPoints.getX()*gridPoints.getY());
        if(!obstaculosPoints[aux].isDefined()){
            obstaculosPoints[aux] = PairPoint(aux/gridPoints.getX(),aux%gridPoints.getX());
            cont++;
        }
    }while(cont < numero);


}

void MainWindow::on_ValueInicioX_valueChanged(int arg1)
{
    inicioPoints.setX(arg1);
    RefreshPoints();
}

void MainWindow::on_ValueInicioY_valueChanged(int arg1)
{
    inicioPoints.setY(arg1);
    RefreshPoints();
}

void MainWindow::on_ValueFinX_valueChanged(int arg1)
{
    finPoints.setX(arg1);
    RefreshPoints();
}

void MainWindow::on_ValueFinY_valueChanged(int arg1)
{
    finPoints.setY(arg1);
    RefreshPoints();
}

void MainWindow::on_SliderObstaculos_valueChanged(int value)
{
    obstaculosp = value;
    if(obstaculosAleatorios)
        RefreshPoints();
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
