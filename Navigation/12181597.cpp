#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Graph;
class road;

class area {
public:
	int num; // 지역 번호
	string name; // 지역 이름
	bool flooded; // 침수 여부 (침수됨:1, 아님:0)
	//area* prev;
	area* next;
	//road* prevRoad; // prev area와 현재 area를 연결하는 road
	road* nextRoad; // next area와 현재 area를 연결하는 road
	int distance;

	char status; // u:unseen, f:fringe, t:tree
	area(int n, string na, bool f) {
		this->num = n;
		this->name = na;
		this->flooded = f;
		//this->prev = NULL;
		this->next = NULL;
		this->nextRoad = NULL;
		//this->status = 'u';
		this->distance = 1000001;
	}
};

class road {
public:
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
public:
	//area* areas[900000] = { NULL, }; //이따 확인해보자. 다 null 차는지
	vector<area*> areas; // 정점을 인덱스(지역번호)로 접근할 수 있는 벡터 (접근 쉽게 하려고)
	vector<area*> areasOnly; // 실제 존재하는(null이 아닌) 정점만을 모아 놓은 벡터 (초기화 쉽게 하려고)
	graph() {
		areas.assign(1000000, NULL);
	}

	void insertArea(int num, string name, bool flooded) {
		area* newNode = new area(num, name, flooded);
		//areas[num] = newNode;
		//areas.push_back(newNode);
		areas[num] = newNode;
		areasOnly.push_back(newNode);
	}
	void insertRoad(int num1, int num2, int d) {
		road* newEdge = new road(num1, num2, d);
		//area* temp1 = areas[num1];
		//area* temp2 = areas[num2];
		//areas[num1]->next = temp2;
		//areas[num1]->nextRoad = newEdge;
		//areas[num2]->next = temp1;
		//areas[num2]->nextRoad = newEdge;

		area *temp1 = new area(areas[num1]->num, areas[num1]->name, areas[num1]->flooded);
		area *temp2 = new area(areas[num2]->num, areas[num2]->name, areas[num2]->flooded);
		area* cur = areas[num1];
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = temp2;
		cur->nextRoad = newEdge;
		cur = areas[num2];
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = temp1;
		cur->nextRoad = newEdge;

		//area *temp1; area *temp2;
		//int check = 0; // num1, num2 다 찾았는지 체크
		//for (area* a : areas) { // area Node 복사하기
		//	if (a->num == num1) {
		//		temp1 = new area(a->num, a->name, a->flooded); // 정보 복사
		//		check++;
		//		if (check == 2)
		//			break;
		//	}
		//	else if (a->num == num2) {
		//		temp2 = new area(a->num, a->name, a->flooded);
		//		check++;
		//		if (check == 2)
		//			break;
		//	}
		//}
		//check = 0;
		//for (area* a : areas) { // area Node & road 이어붙이기
		//	if (a->num == num1) {
		//		// Node 인접리스트의 맨 끝에 이어붙인다.
		//		area* cur = a;
		//		while (cur->next != NULL) {
		//			cur = cur->next;
		//		}
		//		cur->next = temp2;
		//		cur->nextRoad = newEdge;
		//		check++;
		//		if (check == 2)
		//			break;
		//	}
		//	else if (a->num == num2) {
		//		area* cur = a;
		//		while (cur->next != NULL) {
		//			cur = cur->next;
		//		}
		//		cur->next = temp1;
		//		cur->nextRoad = newEdge;
		//		check++;
		//		if (check == 2)
		//			break;
		//	}
		//}
	}

	void minDistance(int sourceNum, int destNum) { //최단거리 찾기
		int treeNum = 0; // tree set에 추가된 지역들의 수

		// 출발지 또는 목적지가 침수되어 있으면 None
		if (areas[sourceNum]->flooded == 1 || areas[destNum]->flooded == 1) {
			cout << "None\n";
			return;
		}

		// 모든 정점을 unseen으로 초기화
		for (area* a : areasOnly) {
			a->status = 'u'; //unseen
			a->distance = 1000001;
		}
		// 시작 정점 찾아 status: tree, d(s,s) = 0 으로 만들기
		area *s = areas[sourceNum];
		s->status = 't';
		treeNum++;
		s->distance = 0;

		// 시작 정점의 인접 정점 status: fringe로 만들기
		area* cur = s;
		while (cur->next != NULL) {
			if (areas[cur->next->num]->flooded == 0) {
				areas[cur->next->num]->status = 'f';
				areas[cur->next->num]->distance = cur->nextRoad->distance; // 여기 다시 보기
				//cur->next->status = 'f';
				//cur->next->distance = cur->nextRoad->distance; // 여기 다시 보기
			}
			cur = cur->next;
		}
		// areasOnly에 fringe가 존재하면 반복
		//bool flag = true; //fringe가 없으면 false
		while (1) {
			// fringe 중 최소거리값을 갖는 정점 선택
			int minDist = 1000002;
			area* minFringe;
			bool flag = false;
			for (area* a : areasOnly) {
				if (a->status == 'f') {
					flag = true; //fringe가 있으면 true
					if (a->distance < minDist) {
						minDist = a->distance;
						minFringe = a;
					}
				}
			}
			if (flag == false)	break;

			minFringe->status = 't';
			treeNum++;
			if (minFringe->num == destNum)
				break;
			cur = minFringe;
			while (cur->next != NULL) {
				if (areas[cur->next->num]->status != 't' && areas[cur->next->num]->flooded == 0) {
					areas[cur->next->num]->status = 'f';
					// 작은 값으로 거리 업데이트
					if (areas[cur->next->num]->distance > (minFringe->distance + cur->nextRoad->distance)) {
						areas[cur->next->num]->distance = minFringe->distance + cur->nextRoad->distance;
					}
					//// 동일하면 지역번호가 작은 값으로
					//else if (areas[cur->next->num]->distance == (minFringe->distance + cur->nextRoad->distance)) {

					//}
				}
				cur = cur->next;
			}
		}
		if (areas[destNum]->distance > 1000000)
			cout << "None\n";
		else
			cout << treeNum << " " << areas[destNum]->distance << " " << 
			areas[sourceNum]->name << " " << areas[destNum]->name << "\n";
	}
	//void fringeExist() { // areasOnly 벡터에 fringe가 존재하는지 여부

	//}
	void minRoute() { //최단경로 찾기

	}
};

int main() {
	int n, m, q;
	int areaNum1; int areaNum2; string areaName; bool flooded; int distance;
	char c;
	cin >> n >> m >> q;
	graph g;
	for (int i = 0; i < n; i++) {
		cin >> areaNum1 >> areaName >> flooded;
		g.insertArea(areaNum1, areaName, flooded);
	}
	for (int i = 0; i < m; i++) {
		cin >> areaNum1 >> areaNum2 >> distance;
		g.insertRoad(areaNum1, areaNum2, distance);
	}
	while (q--) {
		cin >> c >> areaNum1 >> areaNum2;
		if (c == 'A') {
			g.minDistance(areaNum1, areaNum2);
		}
		else { // 'B'

		}
	}
}