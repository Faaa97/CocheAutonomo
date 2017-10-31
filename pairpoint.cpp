#include "pairpoint.hpp"

PairPoint::PairPoint(int x, int y){
    x_ = x;
    y_ = y;
    gScore = INF;
    fScore = INF;
    cameFrom = NULL;
    if((x == -1) && (y == -1))
        undefined = true;
    else
        undefined = false;
}

PairPoint PairPoint::operator=(const PairPoint& p){
    this->setX(p.getX());
    this->setY(p.getY());

    this->gScore = p.getgScore();
    this->fScore = p.getfScore();
    this->cameFrom = p.getcameFrom();

    return *this;
}
bool PairPoint::operator==(const PairPoint& p)const{
    return p.getX() == this->getX() && p.getY() == this->getY();
}
bool PairPoint::operator<(const PairPoint& p)const{
    if(p.getfScore() < this->getfScore()) return true;
    else if(p.getfScore() == this->getfScore() && p.getX() < this->getX()) return true;
    else return (p.getfScore() == this->getfScore()) && (p.getX() == this->getX()) && (p.getY() < this->getY());
}

void PairPoint::setX(int arg){
    x_ = arg;
    undefined = false;
}
void PairPoint::setY(int arg){
    y_ = arg;
    undefined = false;
}
int PairPoint::getX()const{
    if(!undefined)
        return x_;
    return -2;
}
int PairPoint::getY()const{
    if(!undefined)
        return y_;
    return -2;
}

bool PairPoint::isDefined(){
    return !undefined;
}

void PairPoint::setgScore(int g){
    gScore = g;
}
int PairPoint::getgScore()const{
    return gScore;
}

void PairPoint::setfScore(int f){
    fScore = f;
}
int PairPoint::getfScore()const{
    return fScore;
}

void PairPoint::setcameFrom(PairPoint* p){
    cameFrom = p;
}
PairPoint* PairPoint::getcameFrom()const{
    return cameFrom;
}
