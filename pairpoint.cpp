#include "pairpoint.hpp"

PairPoint::PairPoint(int x, int y){
    x_ = x;
    y_ = y;
    if((x == -1) && (y == -1))
        undefined = true;
    else
        undefined = false;
}

PairPoint PairPoint::operator=(const PairPoint& p){
    this->setX(p.getX());
    this->setY(p.getY());

    return *this;
}
bool PairPoint::operator==(const PairPoint& p){
    return p.getX() == this->getX() && p.getY() == this->getY();
}
bool PairPoint::operator<(const PairPoint& p){
    if(p.getX() < this->getX()) return true;
    else return p.getX() == this->getX() && p.getY() < this->getY();

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
