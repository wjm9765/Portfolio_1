#include "Point.hpp"
#include "Clear.hpp"
#include "Get.hpp"
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "Enemy.hpp"

using namespace std;

//https://blockdmask.tistory.com/308 rand()함수 관련 참조


#define Up 1
#define Down 0
#define Left 2
#define Right 3
#define Enter -1
#define sleep_time 2



constexpr int Y_Base = 18;
constexpr int Y_Max= 0;
constexpr int X_left = 0;
constexpr int X_right = 85;


bool drawEgg(int y){//chagne y

    if(Y_Base + y - 4< Y_Max||Y_Base + y > Y_Base) return false;

    Point egg(0,Y_Base+y);
    printf("  @@@@");//here is base
    egg.SetY(Y_Base+y-1);
    printf(" @@@@@@");
    egg.SetY(Y_Base+y-2);
    printf("@@@@@@@@"); 
    egg.SetY(Y_Base+y-3);
    printf(" @@@@@@");
    egg.SetY(Y_Base+y-4);//here is max 
    printf("  @@@@");
    return true;
}



void GameStart(){
    Point a(33,10);
    printf("PRESS ENTER TO START A GAME");
    a.SetXY(26,11);
    printf("Up key move egg up,Down key move egg down");
    
    bool Enemy_ON_OFF = false;
    bool Collision = false;
    int egg_Pos = 0;//this is change of y
    int enemy_Pos = 0;//this is coordinate of x
    int index=-1;

    Enemy one(0,3);
    Enemy two(1,9);
    Enemy three(2,15);

    int score=0;
    while(1){

        for(int i=19;i<=20;i++){
            for(int j=0;j<93;j++){
                a.SetXY(j,i);
                printf("=");
            }
        }//draw ground


        int temp=egg_Pos;
        if(_kbhit()){ 
            int a = get();
            if(a==Up){
                egg_Pos--;
            }
            else if(a==Down){
                egg_Pos++;              
            }
        }

        if(drawEgg(egg_Pos)!=true){
            drawEgg(temp);
            egg_Pos=temp;
        } 


        //related on enemy functions
        srand((unsigned int)time(NULL));
        
        if(Enemy_ON_OFF==true){
            switch(index){
                case 0 :
                    if(one.check_x_position()!=true){
                        Enemy_ON_OFF=false;
                    }
                    else{
                        one.check_x_position();
                        one.drawEnemy();
                    }
                    break;
                case 1 :
                    if(two.check_x_position()!=true){
                        Enemy_ON_OFF=false;
                    }
                    else{
                        two.check_x_position();
                        two.drawEnemy();
                    }
                    break;
                case 2 :
                    if(three.check_x_position()!=true){
                        Enemy_ON_OFF=false;
                    }
                    else{
                        three.check_x_position();
                        three.drawEnemy();
                    }
                    break;
            }
        }
        else if(Enemy_ON_OFF!=true){
            int num=rand();
            switch(num%3){
                case 0 :
                    index=0;
                    one.check_x_position();
                    one.drawEnemy();
                    Enemy_ON_OFF=true;
                    break;
                case 1 :
                    index=1;
                    two.check_x_position();
                    two.drawEnemy();
                    Enemy_ON_OFF=true;
                    break;
                case 2 :
                    index=2;
                    three.check_x_position();
                    three.drawEnemy();
                    Enemy_ON_OFF=true;
                    break;
            }
        }
        //end

        //check if collision
        switch(index){//egg's x: 0~7
            case 0://y=1~5
            if(Y_Base+egg_Pos>=4&&Y_Base+egg_Pos<=9){
                if(one.get_x_position()<=7){
                    Collision=true;
                    break;
                }
                else{
                    break;
                }
            }
            case 1://y=7~11
            if(Y_Base+egg_Pos>=7&&Y_Base+egg_Pos<=15){
                if(two.get_x_position()<=7){
                    Collision=true;
                    break;
                }
                else{
                    break;
                }
            }
            case 2://y=13~17
            if(Y_Base+egg_Pos>=13&&Y_Base+egg_Pos<=Y_Base){
                if(three.get_x_position()<=7){
                    Collision=true;
                    break;
                }
                else{
                    break;
                }
            }
        }


        if(Collision){
            Cls();
            a.SetXY(40,10);
            printf("Game Over");
            a.SetY(11);
            printf("Score:%d\n",score);
            system("pause");
            break;
        }
        else{
            score++;
        }

        //end check if collision
        
        
        



        Cls();
        Sleep(sleep_time);//1s:1000ms
        //if collision, break;
    }




    /*int key = get();
    if(key==-1){
        Cls();
        for(int i=19;i<=20;i++){
            for(int j=0;j<93;j++){
                a.SetXY(j,i);
                printf("=");
            }
        }
        if(drawEgg(0)!=true){
            Cls();
            printf("ERROR");//this is temporarily, should change don't move
        }
        key=get();
    }*/
}