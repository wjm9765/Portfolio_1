#ifndef _GET_
#define _GET_

#include <conio.h>

#define UP 72 //1
#define DOWN 80//0
#define LEFT 75//2
#define RIGHT 77//3
#define ENTER 13//-1
int get(){
    char c;
    while(1){
        if(_kbhit()){
            c=_getch();//if input direction key, first input 224,so c=-32
            if(c==ENTER) return -1;
            else if(c==-32){
                c=_getch();
                switch(c){
                    case LEFT: return 2;
                    case RIGHT: return 3;
                    case UP: return 1;
                    case DOWN: return 0;
                }
            }
        }
    }   
}

#endif