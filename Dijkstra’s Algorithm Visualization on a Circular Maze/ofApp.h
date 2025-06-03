#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon
#include <cstdlib>
#include <queue>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define INF 999999999
#define OPEN 1
#define CLOSE 0


// 3 * 3 미로의 vertex 및 set
// 0 1 2
// 3 4 5
// 6 7 8




class ofApp : public ofBaseApp {

public:
	
	vector<int> min_set;//다익스트라 알고리즘에서 미로의 칸(즉, 집합)을 방문한 순서대로 vector 자료구조에 저장한다.
	int min;//미로의 왼쪽 아래와 오른쪽 아래 중, cost가 더 적은 곳의 집합을 저장한다.


	//adjcency matrix, 10x10 미로를 최대 크기로 잡고 다음과 같이 선언한다. 미로는 undirected weight graph이기 때문에
	//(1,3) weight=50이면 maze[1][3] = 50, maze[3][1]=50 으로 저장한다.
	int maze[100][100];

	//disjoint set에 사용되는 배열, 집합의 최대를 99로 잡고 다음과 같이 선언한다.
	//root에는 node의 총 갯수가 음수로 저장된다.
	int parent[100];


	//disjoint set 자료구조에서 사용되는 find 함수. 시간복잡도 개선을 위해, 아래에 함수는 root에 직접적으로 node를 연결한다.
	int collFind(int i,int j);

	//disjoint set을 합칠 때, node가 적은 것의 집합이 node가 많은 것의 child로 들어갈 수 있게 Union한다.
	void weightUnion(int i, int j);

	int row, col;//maze의 row와 col
	int vertex;//총 node의 개수
	
	//다익스트라 알고리즘에서 사용되는 자료구조
	int* found;
	int* distance;
	//
	
	//미로 생성 후, 미로를 그리도록 하는 flag 값
	int flag_draw_maze = 0;


	//eller's algrithm을 응용하여 완전 미로가 아닌 순환 미로를 생성한다. 순환 미로를 생성하는 이유는,
	//완전 미로는 min까지의 경로가 오직 하나이기 때문에, 다익스트라 알고리즘을 수행하여 가중치를 계산하는 과정이 의미가 없다.
	void circular_path(int n,int m);
	//동적 할당했던 메모리를 전부 해제한다.
	void free_memory();

	//프로그램에 필요한 메모리를 동적할당한다.
	void alloc_memory(int n,int m);
	
	//다익스트라 알고리즘을 수행한다.
	void Dijkstra(int n);
	//다익스트라 알고리즘에 사용된다. 고르지 않는 distance 값 중에 최소의 vertex를 반환한다.
	int choose(int* a, int b, int* c);
	//미로와 다익스트라 알고리즘의 결과값을 그린다.
	void draw_maze();
	




	void setup();
	void update();
	void draw();

	void keyPressed(int key); // Traps escape key if exit disabled
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	
	
	// Menu
	ofxWinMenu* menu; // Menu object
	void appMenuFunction(string title, bool bChecked); // Menu return function

	// Used by example app
	ofTrueTypeFont myFont;
	ofImage myImage;
	float windowWidth, windowHeight;
	HWND hWnd; // Application window
	HWND hWndForeground; // current foreground window

	// Example menu variables
	bool bShowInfo;
	bool bFullscreen;
	bool bTopmost;
	// Example functions
	void doFullScreen(bool bFull);
	void doTopmost(bool bTop);


};