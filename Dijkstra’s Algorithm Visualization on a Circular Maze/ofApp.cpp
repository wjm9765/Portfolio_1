
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth() - windowWidth) / 2, (ofGetScreenHeight() - windowHeight) / 2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Make Maze", false, false); // Not checked and not auto-checked

	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "show Dijkstra",false,false);
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check
	//
	//Tool popup menu
	// 
	// Set the menu to the window
	menu->SetWindowMenu();

	srand(time(NULL));



} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if (title == "Make Maze") {
		circular_path(9, 9); //9*9를 기준으로 하는 랜덤 순환 미로를 생성한다.
	}
	if (title == "Exit") {
		free_memory();//동적 할당했던 메모리를 해제한다.
		ofExit(); // Quit the application(
		
	}

	
	if (title == "show Dijkstra") {//다익스트라의 결과값을 그린다.
		Dijkstra(col / 2);//시작점을 첫 번쨰 줄의 중간 칸이다.
		if (distance[col * (row - 1)] < distance[col - 1 + col * (row - 1)]) {//왼쪽 아래와 오른쪽 아래 중 더 낮은 cost로 갈 수 있는 곳을 min으로 저장한다.
			min = col * (row - 1);
		}
		else {
			min = col - 1 + col * (row - 1);
		}
		//cout << "min " << min << endl;
	}


	if (title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if (title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);
	int i, j;

	
	ofSetColor(100);
	ofSetLineWidth(5);

	

	if (flag_draw_maze) {
		draw_maze();//미로를 그린다.
	}


	if (bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight() - 20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if (bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else {
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU));
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth() - ofGetWidth()) / 2, (ofGetScreenHeight() - ofGetHeight()) / 2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if (bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if (bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if (GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Escape key exit has been disabled but it can be checked here
	if (key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if (bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if (key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if (key == 'f') {
		bFullscreen = !bFullscreen;
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
//
//final project
//

int ofApp::collFind(int i,int j) {
	//i,j는 미로의 행과 열을 나타낸다.
	int set = j + col*i;//i,j를 기반으로 그 칸이 나타내는 set을 계산한다.
	int root, trail, lead;
	for (root = set; parent[root] >= 0; root = parent[root]);
	for (trail = set; trail != root; trail = lead) {//set의 root vertex를 반환한다. 단 모든 vertex를 root에 direct하게 연결한다.
		lead = parent[trail];
		parent[trail] = root;
	}
	return root;
}

void ofApp::weightUnion(int i, int j) {
	int temp = parent[i] + parent[j];//root가 되는 집합은 모든 node의 개수를 음수로 가지고 있다.
	if (parent[i] > parent[j]) {//적은 node를 가지는 집합이 큰 집합의 child로 들어간다. ex) -2>-3 => -2->-3
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

void ofApp::circular_path(int n, int m) {//완전 미로가 아닌 순환 미로를 생성한다.
	//초기화 과정
	row = n;
	col = m;
	int count[100] = { 0 };
	alloc_memory(n, m);//필요한 자료구조들은 동적할당 해준다.
	int temp,weight;//랜덤하게 0,1값과 가중치 값을 저장한다.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < vertex; j++) {//각 행에서 각 집합은 최소 하나의 수직 경로를 가져야하므로, 경로가 있다면 count[집합]=1
			count[j] = 0;
		}

		for (int j = 0; j < m - 1; j++) {//수평 경로를 결정힌다.
			if (i == n - 1) {//만약 마지막 행이라면 모든 경로를 연결한다.
				if (collFind(i, j) != collFind(i, j + 1)) {//단 연결하려는 두 경로가 같은 집합이라면 진행하지 않는다.
					weightUnion(collFind(i, j), collFind(i, j + 1));//경로가 있는 두 set을 union한다.
					weight = rand() % vertex;//랜덤하게 가중치를 결정하여 maze에 저장한다.
					maze[j + col * i][j + 1 + col * i] = weight;
					maze[j + 1 + col * i][j + col * i] = weight;
				}
				continue;
			}
			temp = rand() % 2;//open할지 close할지 랜덤하게 저장한다.
			if (temp == OPEN) {
				//만약 연결하려는 두 경로가 같은 집합이라면 진행하지 않는 것이 완전 미로 생성하는 조건이지만,
				//순환 경로를 생성하는 것이 목표이기 때문에, 그것과 상관없이 진행한다.
					weightUnion(collFind(i, j), collFind(i, j + 1));
					weight = rand() % vertex;
					maze[j + col * i][j + 1 + col * i] = weight;
					maze[j + 1 + col * i][j + col * i] = weight;
				
			}
		}
		//수직 경로를 결정한다.
		for (int j = 0; j < m; j++) {//아래 과정은 위의 과정과 동일하다.
			temp = rand() % 2;
			if (temp == OPEN ) {
				count[j + col * i] = 1;
				weightUnion(collFind(i, j), collFind(i+1, j));
				weight = rand() % vertex;
				maze[j+col*(i+1)][j + col * i] = weight;
				maze[j + col * i][j + col * (i + 1)] = weight;
			}
			//만약 마지막 열이 아니고, 다음 열의 set이 현재 칸의 set과 다르다면, 최소한 한 개의 수직 경로가 있는지 점검한다.
			else if(j!=m-1) {
				if (collFind(i, j) != collFind(i, j + 1)&&!count[j+col*i]) {//만약 수직 경로가 없다면 수직 경로를 생성한다.
					count[j + col * i] = 1;//count 값을 갱신한다.
					weightUnion(collFind(i, j), collFind(i + 1, j));
					weight = rand() % vertex;
					maze[j + col * (i + 1)][j + col * i] = weight;
					maze[j + col * i][j + col * (i + 1)] = weight;
				}
			}
			//만약 마지막 열이고, 그 칸의 set이 수직경로가 하나도 없다면, 수직 경로를 생성한다.
			else if (j == m-1 && !count[j + col * i]) {
				count[j + col * i] = 1;
				weightUnion(collFind(i, j), collFind(i + 1, j));
				weight = rand() % vertex;
				maze[j + col * (i + 1)][j + col * i] = weight;
				maze[j + col * i][j + col * (i + 1)] = weight;
			}
		}
	}

	/*for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}*/


	
	flag_draw_maze = 1;//draw함수에서 그림을 그릴 수 있도록 한다.
}





void ofApp::draw_maze() {
	int min_flag = 1;//두 지점 중 최소 지점에 도달할 시 멈출 flag
	ofSetColor(100);//미로의 테두리 출력
	int top_left_x = 1, top_left_y=1;
	int top_right_x=top_left_x+col*2, top_right_y=1;
	int bot_left_x=1, bot_left_y=1+2*row;
	int bot_right_x=top_right_x, bot_right_y=bot_left_y;
	ofDrawLine(20 * top_left_x, 20 * top_left_y, 20 * top_right_x, 20 * top_right_y);
	ofDrawLine(20 * top_left_x, 20 * top_left_y, 20 * bot_left_x, 20 * bot_left_y);
	ofDrawLine(20 * top_right_x, 20 * top_right_y, 20 * bot_right_x, 20 * bot_right_y);
	ofDrawLine(20 * bot_left_x, 20 * bot_left_y, 20 * bot_right_x, 20 * bot_right_y);
	
	
	
	int s_x, s_y, e_x, e_y;
	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			
			if (i >= j) { //vertex * vertex 이기는 하지만, 실제로는 undirected graph이기 때문에 대각선 기준으로 절반만 확인해도 괜찮다.
				continue;
			}
			
			//i set과 j set 사이에 경로가 존재한다는 뜻이므로, 경로를 그린다.
			//가중치에 따라 경로 색깔을 다르게 한다. 가중치가 높을 수록 밝은 빨강색에 가까워진다.
			if (maze[i][j]<vertex) {
				//set을 기준으로 좌표를 계산한다.
				ofSetColor(12.5 * maze[i][j], 0, 0);
				s_x = (i % col + 1) * 2;
				s_y = (i / col + 1) * 2;
				e_x = (j % col + 1) * 2;
				e_y = (j / col + 1) * 2;
				ofDrawLine(20 * s_x, 20 * s_y, 20 * e_x, 20 * e_y);
				continue;
			}
			//두 set사이에 경로가 없다는 뜻이므로 벽을 그린다.
			else{
				//set을 기준으로 좌표를 계산한다.
				ofSetColor(100);
				if (j - i == col) {// 세로 벽 'ㅡ' 좌표
					s_x = j % col * 2 + 1;
					s_y = j / col * 2 + 1;
					e_x = s_x + 2;
					e_y = s_y;
					ofDrawLine(20 * s_x, 20 * s_y, 20 * e_x, 20 * e_y);
				}
				else if(abs(j-i)==1){//가로 벽 ㅣ 좌표
					s_x = j % col * 2 + 1;
					s_y = j / col * 2 + 1;
					e_x = s_x;
					e_y = s_y + 2;
					ofDrawLine(20 * s_x, 20 * s_y, 20 * e_x, 20 * e_y);
				}
				
			}
			
		}
	}

	//다익스트라 알고리즘을 통해 수행한 결과를 출력한다. 단, 목표 지점인 min까지만 출력하도록 한다.
		for (int i = 0; i < min_set.size(); i++) {
			if (!min_flag) {
				break;
			}
			//min에 도달했으므로 flag 값을 0으로 설정해준다.
			if (min_set[i] == min) {
				min_flag = 0;
			}
			//좌표값을 계산한다.
			s_x = ((min_set[i] % col + 1) * 2);
			s_y = ((min_set[i] / col + 1) * 2);
			
			//처음에서 나중으로 갈 수록 하양색에 가까워진다. 색깔을 통해, 어떤 순서로 vertex를 방문했는지 확인할 수 있다.
			ofSetColor(255,12.5*i , 255);
			ofDrawCircle(20 * s_x, 20 * s_y, 5);
		}
}











void ofApp::alloc_memory(int n, int m) {
	vertex = n * m;//vertex는 미로의 node 총 갯수

	//다익스트라 알고리즘에서 사용되는 자료구조
	found = new int[vertex];//방문했는지 판별하는 자료구조
	distance = new int[vertex];//가중치로 계산한 source vertex에서 걸리는 최소 cost를 저장
	//

	//자료구조 초기화
	for (int i = 0; i < vertex; i++) {
		parent[i] = -1;
		distance[i] = INF;
	}

	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			maze[i][j] = INF;
		}
	}
}

void ofApp::free_memory() {//동적 할당했던 2차원 배열 해제
	
	vector<int>().swap(min_set);
	delete[] found;
	delete[] distance;
	
}

int ofApp::choose(int* distance, int n, int* found) {
	int min = INF;
	int minpos = -1;
	for (int i = 0; i < n; i++) {//found하지 않은 vertex의 distance 값 중에 최소를 고르고, vertex를 반환한다.
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}


//다익스트라 알고리즘, v는 (0,col/2)에 있는 칸의 vertex이다.
void ofApp::Dijkstra(int v) {
	int i, u, w;
	for (i = 0; i < vertex; i++) {//사용될 자료구조의 초기화 작업을 한다.
		found[i] = FALSE;
		distance[i] = maze[v][i];
	}
	found[v] = TRUE;//시작점을 True로 설정한다.
	min_set.push_back(v);//방문한 순서대로 vector 자료구조에 저장한다.
	for (i = 0; i < vertex - 2; i++) {
		u = choose(distance, vertex, found);//found하지 않은 vertex의 distance 값중 최소를 선택한다.
		min_set.push_back(u);//방문한 순서대로 vector 자료구조에 저장한다.
		found[u] = TRUE;//방문한 곳을 True로 설정한다.
		for (w = 0; w < vertex; w++) {
			if(!found[w])//만약 현재보다 가능한 최소 값이 있다면, distance의 값을 갱신한다.
				if (distance[u] + maze[u][w] < distance[w]) {
					distance[w] = distance[u] + maze[u][w];
				}
		}
	}
}

