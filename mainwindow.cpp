#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    opciones = new OpcionesWindow;

    connect(ui->actionOpciones, SIGNAL(triggered()), this, SLOT(on_actionOpciones_triggered()),Qt::UniqueConnection);
    connect(ui->actionSalir, SIGNAL(triggered()), this, SLOT(on_actionSalir_triggered()));
    connect(opciones, SIGNAL(accepted()),this, SLOT( opciones_accepted()));

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
    coche = NULL;

    setGrid();
    setInicio();
    setFin();

}

MainWindow::~MainWindow()
{
    delete ui;
    if(opciones != NULL){
        delete opciones;
        opciones = NULL;
    }
}

void MainWindow::opciones_accepted(){

    PairPoint newGrid = opciones->getGridPoints();
    PairPoint newInicio = opciones->getInicioPoints();
    PairPoint newFin = opciones->getFinPoints();
    bool newObstaculosAleatorios = opciones->getObstaculosAleatorios();
    int newObstaculosPorcentaje = opciones->getObstaculosPorcentaje();

    if(gridPoints != newGrid){
        gridPoints = newGrid;
        refreshGrid();
    }

    if(inicioPoints != newInicio){
        inicioPoints = newInicio;
        setInicio();
    }
    if(finPoints != newFin){
        finPoints = newFin;
        setFin();
    }
    if(obstaculosAleatorios != newObstaculosAleatorios){
        obstaculosAleatorios = newObstaculosAleatorios;
        obstaculosDefinidos = false;
        //volvemos a hacer los obstáculos
    }
    if(obstaculosp != newObstaculosPorcentaje){
        obstaculosp = newObstaculosPorcentaje;
        obstaculosDefinidos = false;
        //volvemos a hacer los obstáculos
    }
}

void MainWindow::setGrid(){
    scene = new QGraphicsScene(this);
    //ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    for(int i = 0; i < gridPoints.getX(); i++)
        for(int j = 0; j < gridPoints.getY(); j++){
            gridRectangles.push_back(scene->addRect(i*gridSize, j*gridSize, gridSize, gridSize, outlinePen, QBrush(Qt::white)));
            gridNodes.push_back(PairPoint(i+1,j+1));
        }
    for(unsigned i = 0; i < gridRectangles.size(); i++)
        gridRectangles[i]->setZValue(GRIDZ);
}

void MainWindow::refreshGrid(){
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    for(unsigned i = 0; i < gridRectangles.size(); i++)
        delete gridRectangles[i];

    gridRectangles.resize(0);
    gridNodes.resize(0);

    for(int i = 0; i < gridPoints.getX(); i++)
        for(int j = 0; j < gridPoints.getY(); j++){
            gridRectangles.push_back(scene->addRect(i*gridSize, j*gridSize, gridSize, gridSize, outlinePen, QBrush(Qt::white)));
            gridNodes.push_back(PairPoint(i+1,j+1));
        }
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

void MainWindow::setObstaculos(){

    if(!obstaculosDefinidos){

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
        obstaculosDefinidos = true;
    }
    else{
        for(unsigned i = 0; i < obstaculos.size(); i++)
            delete obstaculos[i];
        obstaculos.resize(0);
    }


    for(unsigned i = 0; i < obstaculosPoints.size(); i++)
        if(obstaculosPoints[i].isDefined())
            obstaculos.push_back(scene->addRect(obstaculosPoints[i].getX()*gridSize,obstaculosPoints[i].getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::black), QBrush(Qt::black)));

}

void MainWindow::setCoche(){

    if (coche != NULL){
        delete coche;
        coche = NULL;
    }

    if(cochePoints.isDefined())
        coche = scene->addRect((cochePoints.getX()-1)*gridSize,(cochePoints.getY()-1)*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::green), QBrush(Qt::green));
    coche->setZValue(5);
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

void MainWindow::on_actionOpciones_triggered()
{
    opciones->show();
}

std::list<PairPoint*> MainWindow::AStar(){

    int start = (inicioPoints.getY()-1)+(inicioPoints.getX()-1)*gridPoints.getX();
    int fin = (finPoints.getY()-1)+(finPoints.getX()-1)*gridPoints.getX();

    cochePoints = gridNodes[start];
    gridNodes[start].setgScore(0);
    openSet.insert(&gridNodes[start]);
    closedSet.clear();

    gridNodes[start].setfScore(manhattanHeuristic(gridNodes[start]));
    std::cout << "inicio = (" << inicioPoints.getX() << "," << inicioPoints.getY() << ")" << std::endl;
     std::cout << "FIN = (" << gridNodes[fin].getX() << "," << gridNodes[fin].getY() << ")" << std::endl;
    while(!openSet.empty()){
        PairPoint* current = *openSet.begin();
        if(current == &gridNodes[fin])
            return reconstructPath(current);
        openSet.erase(current);
        closedSet.insert(current);

        visitadosPoints.push_back(PairPoint(current->getX(),current->getY()));
        setVisitado();

        std::vector<int> vecinos;
        int aux = current->getX()-1 + (current->getY()-2)*gridPoints.getX();//Vecino superior
        if(current->getX() > 0 && current->getY()-1 > 0)
            vecinos.push_back(aux);
        aux = current->getX()-2 + (current->getY()-1)*gridPoints.getX();//Vecino izquierdo
        if(current->getX()-1 > 0 && current->getY() > 0)
            vecinos.push_back(aux);
        aux = current->getX()-1 + current->getY()*gridPoints.getX();//Vecino inferior
        if(current->getX() > 0 && current->getY()+1 > 0)
            vecinos.push_back(aux);
        aux = current->getX() + (current->getY()-1)*gridPoints.getX();//Vecino derecho
        if(current->getX()+1 > 0 && current->getY() > 0)
            vecinos.push_back(aux);


        std::cout<< "Vecinos("<< current->getX()<<","<<current->getY()<<") = " << vecinos.size() << std::endl;


        for(unsigned i = 0; i < vecinos.size(); i++){
            std::cout <<"iter: " << i << std::endl;
             std::cout <<"vecino" <<i<<": ("<< gridNodes[vecinos[i]].getX() <<","<<gridNodes[vecinos[i]].getY()<<")"<<std::endl;

            if(closedSet.find(&gridNodes[vecinos[i]]) != closedSet.end()){    //Si se encuentra en closedSet...
                std::cout <<"Se encuentra en closedSet" << std::endl;
                continue;
            }
            if(openSet.find(&gridNodes[vecinos[i]]) == openSet.end()){           //Si no se encuentra en openSet...
                std::cout <<"No se encuentra en openSet" << std::endl;
                openSet.insert(&gridNodes[vecinos[i]]);
            }
            int gScoreNew = current->getgScore() + 1; //La distancia entre un nodo y el vecino es de 1(m)
            std::cout << "gScore: " << current->getgScore() << " new: " <<gScoreNew << std::endl;
            if(gScoreNew >= gridNodes[vecinos[i]].getgScore()){
                std::cout << "No es camino mínimo" << std::endl;
                continue;
            }
            gridNodes[vecinos[i]].setcameFrom(current);
            gridNodes[vecinos[i]].setgScore(gScoreNew);
            gridNodes[vecinos[i]].setfScore(gridNodes[vecinos[i]].getgScore() + manhattanHeuristic(gridNodes[vecinos[i]]));
            std::cout << "Encontrado nuevo camino: iter: " << i << std::endl;
        }
    }
    return std::list<PairPoint*>(); //lista vacía, por que no hay camino mínimo
}

int MainWindow::manhattanHeuristic(PairPoint node){
    int auxX = abs(node.getX() - finPoints.getX());
    int auxY = abs(node.getY() - finPoints.getY());
    return auxX + auxY;
}

int MainWindow::searchlowestfScore(){
    int min = INF;
    int pos = 0;
    for(unsigned i = 0; i < gridNodes.size(); i++){
        if(gridNodes[i].getfScore() < min){
            min = gridNodes[i].getfScore();
            pos = i;
        }
    }
    return pos;
}

std::list<PairPoint*> MainWindow::reconstructPath(PairPoint* current){
    std::list<PairPoint*> caminoMinimo;
    caminoMinimo.push_back(current);

    int aux = searchCameFrom(current);
    while(aux != -1){
        current = &gridNodes[aux];
        caminoMinimo.push_back(current);
        aux = searchCameFrom(current);
    }
    return caminoMinimo;
}

int MainWindow::searchCameFrom(PairPoint* node){
    for(unsigned i = 0; i < gridNodes.size(); i++){
        if(gridNodes[i].getcameFrom() == node)
            return i;
    }
    return -1;
}

void MainWindow::setVisitado(){

    if(visitados.size() != 0){
        for(unsigned i = 0; i < visitados.size(); i++)
            delete visitados[i];
        visitados.resize(0);
    }
    for(unsigned i = 0; i < visitadosPoints.size(); i++)
        visitados.push_back(scene->addRect((visitadosPoints[i].getX()-1)*gridSize,(visitadosPoints[i].getY()-1)*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::yellow), QBrush(Qt::yellow)));
}

void MainWindow::on_actionSalir_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionStart_triggered(){
    std::list<PairPoint*> caminoMinimo = AStar();
    if(caminoMinimo.size() != 0){};
    //setCoche();
}
