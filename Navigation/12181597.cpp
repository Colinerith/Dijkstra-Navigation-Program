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
	area* next;
	road* nextRoad; // next area�� ���� area�� �����ϴ� road
	int distance;

	char status; // u:unseen, f:fringe, t:tree
	area(int n, string na, bool f) {
		this->num = n;
		this->name = na;
		this->flooded = f;
		this->next = NULL;
		this->nextRoad = NULL;
		this->distance = 1000001;
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
	vector<area*> areas; // ������ �ε���(������ȣ)�� ������ �� �ִ� ���� (���� ���� �Ϸ���)
	vector<area*> areasOnly; // ���� �����ϴ�(null�� �ƴ�) �������� ��� ���� ���� (�ʱ�ȭ ���� �Ϸ���)
	graph() {
		areas.assign(1000000, NULL);
	}

	void insertArea(int num, string name, bool flooded) {
		area* newNode = new area(num, name, flooded);
		areas[num] = newNode;
		areasOnly.push_back(newNode);
	}
	void insertRoad(int num1, int num2, int d) {
		road* newEdge = new road(num1, num2, d);

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
	}

	void minDistance(int sourceNum, int destNum) { //�ִܰŸ� ã��
		int treeNum = 0; // tree set�� �߰��� �������� ��

		// ����� �Ǵ� �������� ħ���Ǿ� ������ None
		if (areas[sourceNum]->flooded == 1 || areas[destNum]->flooded == 1) {
			cout << "None\n";
			return;
		}

		// ��� ������ unseen���� �ʱ�ȭ
		for (area* a : areasOnly) {
			a->status = 'u'; //unseen
			a->distance = 1000001;
		}
		// ���� ���� ã�� status: tree, d(s,s) = 0 ���� �����
		area *s = areas[sourceNum];
		s->status = 't';
		treeNum++;
		s->distance = 0;

		// ���� ������ ���� ���� status: fringe�� �����
		area* cur = s;
		while (cur->next != NULL) {
			if (areas[cur->next->num]->flooded == 0) {
				areas[cur->next->num]->status = 'f';
				areas[cur->next->num]->distance = cur->nextRoad->distance;
			}
			cur = cur->next;
		}
		// areasOnly�� fringe�� �����ϸ� �ݺ�
		while (1) {
			// fringe �� �ּҰŸ����� ���� ���� ����
			int minDist = 1000002;
			area* minFringe;
			bool flag = false;
			for (area* a : areasOnly) {
				if (a->status == 'f') {
					flag = true; //fringe�� ������ true
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
					// ���� ������ �Ÿ� ������Ʈ
					if (areas[cur->next->num]->distance > (minFringe->distance + cur->nextRoad->distance)) {
						areas[cur->next->num]->distance = minFringe->distance + cur->nextRoad->distance;
					}
					//// �����ϸ� ������ȣ�� ���� ������
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
	void minRoute() { //�ִܰ�� ã��

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