#ifndef PAIRPOINT_H
#define PAIRPOINT_H


class PairPoint{
private:
    int x_;
    int y_;
    bool undefined;
public:
    PairPoint(int x = -1, int y = -1);
    void setX(int arg);
    void setY(int arg);
    int getX();
    int getY();
    bool isDefined();
};

#endif // PAIRPOINT_H
