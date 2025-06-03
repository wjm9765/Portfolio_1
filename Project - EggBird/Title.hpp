#include <stdio.h>
#include "Point.hpp"
#include "Get.hpp"
#include "Clear.hpp"
#include "GameStart.hpp"

void title(){
    printf("\n\n\n");//3 lines empty
    printf("\t=============================================================================\n");
    printf("\t******       *****         *****          ******   *****   *****     *****\n"); 
    printf("\t*          **     **     **    **         *     *    *     *    *    *    *\n"); 
    printf("\t*         *             *                 *     *    *     *    *    *     *\n");
    printf("\t******    *     *****   *     *****       ******     *     *****     *      *\n");
    printf("\t*         *    *   *    *    *   *        *     *    *     *    *    *     *\n");
    printf("\t*          **     *      **     *         *     *    *     *     *   *    *\n");
    printf("\t******       *****         *****          ******   *****   *      *  *****\n");
    printf("\t=============================================================================\n");

    Point start(44,15);
    printf("start");//start
    Point end(44,18);
    printf("end");//end

    /*Point cursor(40,15);
    printf("->");

    //up 1 down 0 left 2 right 3, if enter -1 
    int key=get();
    do{
        //if point is start and input is 1, don't move
        //we need point class
        if(key==1){
            if(cursor.GetY()==15){} //do not anything
            else{
                cursor.SetY(18);
                printf("->");
            }
        }
        if(key==0){
            if(cursor.GetY()==18){}//do not anything
            else cursor.SetY(15);
        }
    }while(key!=-1);*/
}

void Title_move(){
    title();
    Point cursor(40,15);
    printf("->");

    
    //up 1 down 0 left 2 right 3, if enter -1 
    int key=get();
    while(key!=-1){
        //if point is start and input is 1, don't move
        //we need point class
        if(key==1){
            if(cursor.GetY()==15){} //do not anything
            else{
                Cls();
                title();
                cursor.SetY(15);
                printf("->");
            }
        }
        else if(key==0){
            if(cursor.GetY()==18){}//do not anything
            else{
                Cls();
                title();
                cursor.SetY(18);
                printf("->");
            }
        }
        key=get();
    }


    switch(cursor.GetY()){
        case 15: Cls();
                 GameStart();
        case 18: return;
    }
}