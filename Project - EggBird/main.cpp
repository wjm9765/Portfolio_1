#include <windows.h>
#include "Title.hpp"


//#include <conio.h>
//#include <stdio.h>


void set(){
    system("mode con:cols=93 lines=25 | title EggBird");
    CONSOLE_CURSOR_INFO cursorInfo = {0,};
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursorInfo);
}


int main(void){
    set();//set basic console
    Title_move();//print title
    
    return 0;
}


/*int main(void) {
    char c;
    while (1) {
        if (_kbhit()) {               // 2. while문안에서 키보드 눌렸을 시 if문이 실행된다.
            c = _getch();           // 3. 방향키가 입력됬을 때 224 00 이 버퍼에 있다. 224부터 빼준다. 
            if (c == -32) {           // 4. -32로 입력되면
                c = _getch();        // 5. 뒤의 값 00을 판별하여 좌우상하 출력
                switch (c) {           
                case LEFT:
                    printf("left\n");
                    break;
                case RIGHT:
                    printf("right\n");
                    break;
                case UP:
                    printf("up\n");
                    break;
                case DOWN:
                    printf("down\n");
                    break;
                }
            }
        }
    }
    return 0;
}*/