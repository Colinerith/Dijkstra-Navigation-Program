#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Graph;
class Road;

class area {
public:
	int num; // ���� ��ȣ
	string name; // ���� �̸�
	bool flooded; // ħ�� ���� (ħ����:1, �ƴ�:0)
	//area* prev;
	area* next;
	//road* prevRoad; // prev area�� ���� area�� �����ϴ� road
	road* nextRoad; // next area�� ���� area�� �����ϴ� road
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
	int area1; // ������ȣ 1
	int area2; // ������ȣ 2
	int distance; // ������ �Ÿ�
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