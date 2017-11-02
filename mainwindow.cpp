#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Coche Autónomo");

    opciones = new OpcionesWindow;

    connect(ui->actionOpciones, SIGNAL(triggered()), this, SLOT(on_actionOpciones_triggered()),Qt::UniqueConnection);
    connect(ui->actionSalir, SIGNAL(triggered()), this, SLOT(on_actionSalir_triggered()));
    connect(opciones, SIGNAL(accepted()),this, SLOT( opciones_accepted()));

    gridSize = 30;
    gridPoints.setX(10);
    gridPoints.setY(10);
    inicioPoints.setX(0);
    inicioPoints.setY(0);
    finPoints.setX(9);
    finPoints.setY(9);
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
        obstaculosDefinidos = false;    //No tiene sentido seguir usando los mismos obstáculos
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
    if(obstaculosAleatorios != newObstaculosAleatorios || obstaculosp != newObstaculosPorcentaje){
        obstaculosAleatorios = newObstaculosAleatorios;
        obstaculosDefinidos = false;
        if(obstaculosp != newObstaculosPorcentaje)
            obstaculosp = newObstaculosPorcentaje;
        //volvemos a hacer los obstáculos
        setObstaculos();
    }
}

void MainWindow::setGrid(){
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(1);

    for(int i = 0; i < gridPoints.getX(); i++)
        for(int j = 0; j < gridPoints.getY(); j++){
            gridRectangles.push_back(scene->addRect(i*gridSize, j*gridSize, gridSize, gridSize, outlinePen, QBrush(Qt::white)));
            gridNodes.push_back(PairPoint(i,j));
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
            gridNodes.push_back(PairPoint(i,j));
        }
    for(unsigned i = 0; i < gridRectangles.size(); i++)
        gridRectangles[i]->setZValue(GRIDZ);
}

void MainWindow::setInicio(){
    if (inicio != NULL){
        delete inicio;
        inicio = NULL;
    }
    if( (inicioPoints.getX() >= 0 && inicioPoints.getX() <= gridPoints.getX()) && (inicioPoints.getY() >= 0 && inicioPoints.getY() <= gridPoints.getY()) )
        inicio = scene->addRect(inicioPoints.getX()*gridSize, inicioPoints.getY()*gridSize, gridSize-1, gridSize-1, QPen(Qt::blue), QBrush(Qt::blue));
    inicio->setZValue(1);
}

void MainWindow::setFin(){
    if (fin != NULL){
        delete fin;
        fin = NULL;
    }
    if( (finPoints.getX() >= 0 && finPoints.getX() <= gridPoints.getX()) && (finPoints.getY() >= 0 && finPoints.getY() <= gridPoints.getY()) )
        fin = scene->addRect(finPoints.getX()*gridSize, finPoints.getY()*gridSize, gridSize-1, gridSize-1, QPen(Qt::red), QBrush(Qt::red));
    fin->setZValue(1);
}

void MainWindow::resizeEvent(QResizeEvent *){
    ui->graphicsView->setGeometry(0,0,this->width(),this->height()-gridSize);
}

void MainWindow::setObstaculos(){

    if(!obstaculosDefinidos){

        GenerarObstaculos();
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

    for(unsigned i = 0; i < obstaculos.size(); i++)
        obstaculos[i]->setZValue(2);
}

void MainWindow::setCoche(){

    if (coche != NULL){
        delete coche;
        coche = NULL;
    }

    if(cochePoints.isDefined())
        coche = scene->addRect(cochePoints.getX()*gridSize,cochePoints.getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::green), QBrush(Qt::green));
    coche->setZValue(5);
}

void MainWindow::GenerarObstaculos(){

    double numero = double(gridPoints.getX() * gridPoints.getY()) * double(obstaculosp)/100;
    int cont = 0;

    srand(time(NULL));

    do{
        int aux = (rand()*clock())% (gridPoints.getX()*gridPoints.getY());
        int ini = inicioPoints.getY() + inicioPoints.getX()*gridPoints.getX();
        int fi = finPoints.getY() + finPoints.getX()*gridPoints.getX();
        if(!obstaculosPoints[aux].isDefined() && aux != ini && aux != fi){
            int x = aux/gridPoints.getX();
            int y = aux%gridPoints.getX();
            obstaculosPoints[aux] = PairPoint(x,y);
            int index = y + x * gridPoints.getX();
            printf("Haciendo obstáculo en (%d,%d)(%d) [%d,%d]\n",gridNodes[index].getX(),gridNodes[index].getY(),index,x,y);
            gridNodes[index].setObstaculo(true);
            cont++;
        }
    }while(cont < numero);

}

void MainWindow::on_actionOpciones_triggered()
{
    opciones->show();
}

std::list<PairPoint*> MainWindow::AStar(){

    int start = inicioPoints.getY()+inicioPoints.getX()*gridPoints.getX();
    int fin = finPoints.getY()+finPoints.getX()*gridPoints.getX();

    cochePoints = gridNodes[start];
    gridNodes[start].setgScore(0);
    openSet.insert(&gridNodes[start]);
    closedSet.clear();

    gridNodes[start].setfScore(manhattanHeuristic(gridNodes[start]));

    while(!openSet.empty()){
        PairPoint* current = *openSet.begin();
        if(current == &gridNodes[fin])
            return reconstructPath(current);
        printf("Current: (%d,%d)\n",current->getX(),current->getY());
        printf("Es obstaculo: %d\n",current->esObstaculo());
        openSet.erase(current);
        closedSet.insert(current);

        visitadosPoints.push_back(PairPoint(current->getX(),current->getY()));
        setVisitado();

        std::vector<int> vecinos;
        int aux = current->getY() + (current->getX()-1) * gridPoints.getX();//Vecino superior
        if(current->getY() >= 0 && current->getY() < gridPoints.getY() && current->getX()-1 >= 0 && current->getX()-1 < gridPoints.getX() && !current->esObstaculo())
            vecinos.push_back(aux);
        aux = current->getY()-1 + current->getX() * gridPoints.getX();//Vecino izquierdo
        if(current->getY()-1 >= 0 && current->getY()-1 < gridPoints.getY() && current->getX() >= 0 && current->getX() < gridPoints.getX() && !current->esObstaculo())
            vecinos.push_back(aux);
        aux = current->getY() + (current->getX()+1) * gridPoints.getX();//Vecino inferior
        if(current->getY() >= 0 && current->getY() < gridPoints.getY() && current->getX()+1 >= 0 && current->getX()+1 < gridPoints.getX() && !current->esObstaculo())
            vecinos.push_back(aux);
        aux = current->getY()+1 + current->getX() * gridPoints.getX();//Vecino derecho
        if(current->getY()+1 >= 0 && current->getY()+1 < gridPoints.getY() && current->getX() >= 0 && current->getX() < gridPoints.getX() && !current->esObstaculo())
            vecinos.push_back(aux);

        for(unsigned i = 0; i < vecinos.size(); i++){
            if(closedSet.find(&gridNodes[vecinos[i]]) != closedSet.end())    //Si se encuentra en closedSet...
                continue;

            if(openSet.find(&gridNodes[vecinos[i]]) == openSet.end())           //Si no se encuentra en openSet...
                openSet.insert(&gridNodes[vecinos[i]]);

            int gScoreNew = current->getgScore() + 1; //La distancia entre un nodo y el vecino es de 1(m)
            if(gScoreNew >= gridNodes[vecinos[i]].getgScore())
                continue;

            gridNodes[vecinos[i]].setcameFrom(current);
            gridNodes[vecinos[i]].setgScore(gScoreNew);
            gridNodes[vecinos[i]].setfScore(gridNodes[vecinos[i]].getgScore() + manhattanHeuristic(gridNodes[vecinos[i]]));
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

    PairPoint* aux = current->getcameFrom();
    while(aux != NULL){
        caminoMinimo.push_back(aux);
        aux = aux->getcameFrom();
    }
    return caminoMinimo;
}

void MainWindow::on_actionSalir_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionStart_triggered(){
    std::list<PairPoint*> caminoMinimo = AStar();
    if(caminoMinimo.size() != 0){
        setCoche();
        for(std::list<PairPoint*>::iterator it = caminoMinimo.begin(); it != caminoMinimo.end(); ++it){
            scene->addRect((*it)->getX()*gridSize,(*it)->getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::magenta), QBrush(Qt::magenta));
        }
        for(std::list<PairPoint*>::reverse_iterator it = caminoMinimo.rbegin(); it != caminoMinimo.rend(); ++it){
            delay(500);
            cochePoints.setX((*it)->getX());
            cochePoints.setY((*it)->getY());
            setCoche();
        }
    }
    printf("No hay camino mínimo\n");
    //Si no hay camino mínimo, mostrar error
}

void MainWindow::delay(int msec){
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::setVisitado(){

    if(visitados.size() != 0){
        for(unsigned i = 0; i < visitados.size(); i++)
            delete visitados[i];
        visitados.resize(0);
    }
    for(unsigned i = 0; i < visitadosPoints.size(); i++)
        visitados.push_back(scene->addRect(visitadosPoints[i].getX()*gridSize,visitadosPoints[i].getY()*gridSize,gridSize-1, gridSize-1 ,QPen(Qt::yellow), QBrush(Qt::yellow)));
}
