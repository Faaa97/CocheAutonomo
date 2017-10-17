#include "pairpoint.hpp"

PairPoint::PairPoint(int x, int y){
    x_ = x;
    y_ = y;
    if((x == -1) && (y == -1))
        undefined = true;
    else
        undefined = false;
}

void PairPoint::setX(int arg){
    x_ = arg;
    undefined = false;
}
void PairPoint::setY(int arg){
    y_ = arg;
    undefined = false;
}
int PairPoint::getX(){
    if(!undefined)
        return x_;
    return -2;
}
int PairPoint::getY(){
    if(!undefined)
        return y_;
    return -2;
}


bool PairPoint::isDefined(){
    return !undefined;
}
