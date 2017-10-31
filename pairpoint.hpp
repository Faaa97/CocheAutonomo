#ifndef PAIRPOINT_H
#define PAIRPOINT_H

#include <cstddef>

const int INF = 9999;

class PairPoint{
private:
    int x_;
    int y_;
    bool undefined;

    int gScore;
    int fScore;
    PairPoint* cameFrom;

public:
    PairPoint(int x = -1, int y = -1);
    void setX(int arg);
    void setY(int arg);
    int getX()const;
    int getY()const;
    bool isDefined();

    void setgScore(int g);
    int getgScore()const;

    void setfScore(int f);
    int getfScore()const;

    void setcameFrom(PairPoint* p);
    PairPoint* getcameFrom()const;

    PairPoint operator=(const PairPoint& p);
    bool operator!=(const PairPoint& p)const;
    bool operator==(const PairPoint& p)const;
    bool operator<(const PairPoint& p)const;
};

#endif // PAIRPOINT_H
