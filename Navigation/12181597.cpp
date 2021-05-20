#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Graph;
class road;

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
public:
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
public:
	//area* areas[900000] = { NULL, }; //�̵� Ȯ���غ���. �� null ������
	vector<area*> areas;
	graph() {
		
	}

	void insertArea(int num, string name, bool flooded) {
		area* newNode = new area(num, name, flooded);
		//areas[num] = newNode;
		areas.push_back(newNode);
	}
	void insertRoad(int num1, int num2, int d) {
		road* newEdge = new road(num1, num2, d);
		//area* temp1 = areas[num1];
		//area* temp2 = areas[num2];
		//areas[num1]->next = temp2;
		//areas[num1]->nextRoad = newEdge;
		//areas[num2]->next = temp1;
		//areas[num2]->nextRoad = newEdge;
		area *temp1; area *temp2;
		int check = 0; // num1, num2 �� ã�Ҵ��� üũ
		for (area* a : areas) { // area Node �����ϱ�
			if (a->num == num1) {
				temp1 = new area(a->num, a->name, a->flooded); // ���� ����
				check++;
				if (check == 2)
					break;
			}
			else if (a->num == num2) {
				temp2 = new area(a->num, a->name, a->flooded);
				check++;
				if (check == 2)
					break;
			}
		}
		check = 0;
		for (area* a : areas) { // area Node & road �̾���̱�
			if (a->num == num1) {
				// Node ��������Ʈ�� �� ���� �̾���δ�.
				area* cur = a;
				while (cur->next != NULL) {
					cur = cur->next;
				}
				cur->next = temp2;
				cur->nextRoad = newEdge;
				check++;
				if (check == 2)
					break;
			}
			else if (a->num == num2) {
				area* cur = a;
				while (cur->next != NULL) {
					cur = cur->next;
				}
				cur->next = temp1;
				cur->nextRoad = newEdge;
				check++;
				if (check == 2)
					break;
			}
		}
	}
};

int main() {
	int n, m, q;
	int areaNum1; int areaNum2; string areaName; bool flooded; int distance;
	cin >> n >> m >> q;
	graph g;
	for (int i = 0; i < n; i++) {
		cin >> areaNum1 >> areaName >> flooded;
		g.insertArea(areaNum1, areaName, flooded);
	}
	for (int i = 0; i < n; i++) {
		cin >> areaNum1 >> areaNum2 >> distance;
		g.insertRoad(areaNum1, areaNum2, distance);
	}
}