#ifndef POINT_CLASS
#define POINT_CLASS

#include <windows.h>

class Point{//in this project, we don't use 'new' 
private:
    COORD pos;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get hadnle from window
public:
    Point(int x,int y){
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(handle,pos);//print point
    }

    void SetX(int x){
        pos.X=x;
        SetConsoleCursorPosition(handle,pos);//print point
    }
    void SetY(int y){
        pos.Y=y;
        SetConsoleCursorPosition(handle,pos);//print point
    }
    void SetXY(int x,int y){
        pos.X=x;
        pos.Y=y;
        SetConsoleCursorPosition(handle,pos);//print point
    }

    int GetX(){
        return pos.X;
    }
    int GetY(){
        return pos.Y;
    }
};

//https://blog.naver.com/skyvvv624/222593571935 커서 안보이게 하기

/*void point(int x,int y){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//get hadnle from window
    COORD pos;//point sturcture
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);//print point
}*/

#endif