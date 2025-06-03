#ifndef ENEMY_CLASS
#define ENEMY_CLASS

#include "Point.hpp"
#include <cstddef>

class Enemy{
private:
    int index;
    int y_position;\
    Point *a;
    int x_position=85;
public:
    ~Enemy(){
        delete a;
    }
    Enemy(int index_,int y_):index(index_),y_position(y_){}

    int get_x_position(){
        return x_position;
    }

    bool check_x_position();//if enemy until move return true,no move return false
    void drawEnemy();
};



#endif