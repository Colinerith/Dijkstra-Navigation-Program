#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Graph;
class Road;

class area {
public:
	int num; // 지역 번호
	string name; // 지역 이름
	bool flooded; // 침수 여부 (침수됨:1, 아님:0)
	//area* prev;
	area* next;
	//road* prevRoad; // prev area와 현재 area를 연결하는 road
	road* nextRoad; // next area와 현재 area를 연결하는 road
	area(int n, string na, bool f) {
		this->num = n;
		this->name = na;
		this->flooded = f;
		//this->prev = NULL;
		this->next = NULL;
		this->nextRoad = NULL;
	}
};

class road {
	int area1; // 지역번호 1
	int area2; // 지역번호 2
	int distance; // 도로의 거리
	road(int n1, int n2, int di) {
		this->area1 = n1;
		this->area2 = n2;
		this->distance = di;
	}
};

class graph {
	vector<area*> areas;
	graph() {

	}
};