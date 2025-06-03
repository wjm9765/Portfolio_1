#include "Enemy.hpp"
#include <iostream>


bool Enemy::check_x_position(){
    if(x_position>0){
        x_position--;
        return true;
    }
    else{
        x_position=85;
        return false;
    }
}
void Enemy::drawEnemy(){
    a = new Point(x_position,y_position-2);
    printf("  #  #");
    a->SetY(y_position-1);
    printf(" # ## #");
    a->SetY(y_position);
    printf("#######");//here is x,y position
    a->SetY(y_position+1);
    printf(" # ## #");
    a->SetY(y_position+2);
    printf("  #  #");
}