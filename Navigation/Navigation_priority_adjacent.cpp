//adjacency list와 priority queue를 이용해 구현
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

class adjacent { // 연결 리스트 구현에 필요한 노드(인접 지역)
public:
	int areaNum; // 지역 번호
	int distance; // 거리
	adjacent* next; // 다음 노드(지역)
	adjacent(int a, int d) {
		areaNum = a;
		distance = d;
		next = NULL;
	}
};

struct comp { // 거리 기준 정렬, 거리가 같다면 지역번호 기준 정렬
	bool operator()(pair<int, int> a, pair<int, int> b) {
		if (a.second == b.second)
			return a.first > b.first;
		return a.second > b.second;
	}
};

string areas[1000000]; // 지역 이름을 저장하기 위한 배열
int distances[1000000]; // 최단거리를 저장하기 위한 배열
int predecessor[1000000]; // 경로를 추적하기 위한 배열
vector<adjacent*> roads(1000000); // 도로를 저장하기 위한 adjacency list

void minDist(int sourceNum, int destNum) {
	if (areas[sourceNum] == "" || areas[destNum] == "") { // 침수된 지역이 포함되었으면
		cout << "None\n";
		return;
	}

	int treeNum = 0;
	for (int i = 100000; i < 1000000; i++) // 배열 초기화
		distances[i] = 1000000;
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> fringeQ; // fringe node를 저장하기 위한 우선순위 큐

	fringeQ.push({ sourceNum, 0 });
	distances[sourceNum] = 0;

	int curNum, distance;
	while (!fringeQ.empty()) {
		curNum = fringeQ.top().first; // 현재 지역 번호
		distance = fringeQ.top().second; // 거리
		fringeQ.pop();

		if (distances[curNum] < distance) // 이미 확인했고, 더 짧다면 무시
			continue;
		treeNum++; // 무시되지 않는다면 fringe -> tree 노드가 됨

		if (curNum == destNum) // 도착 노드가 tree 됐다면 종료
			break;
		
		int next, nextDistance;
		adjacent* cur = roads[curNum];
		while (cur != NULL) { // 연결된 지역들 탐색
			next = cur->areaNum; // 연결된 지역 번호
			nextDistance = distance + cur->distance;
			if (nextDistance < distances[next]) { // 거리 갱신
				fringeQ.push({ next, nextDistance }); // fringe 큐에 넣기
				distances[next] = nextDistance;
			}
			cur = cur->next;
		}
	}

	if (distances[destNum] > 100000) cout << "None\n";
	else cout << treeNum << " " << distances[destNum] << " " << areas[sourceNum] << " " << areas[destNum] << "\n";
}

void minRoute(int sourceNum, int destNum) {
	if (areas[sourceNum] == "" || areas[destNum] == "") { // 침수된 지역이 포함되었으면
		cout << "None\n";
		return;
	}

	int treeNum = 0;
	for (int i = 100000; i < 1000000; i++) // 배열 초기화
		distances[i] = 1000000;
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> fringeQ; // fringe node를 저장하기 위한 우선순위 큐

	fringeQ.push({ sourceNum, 0 });
	distances[sourceNum] = 0;

	int curNum, distance;
	while (!fringeQ.empty()) {
		curNum = fringeQ.top().first; // 현재 지역 번호
		distance = fringeQ.top().second; // 거리
		fringeQ.pop();

		if (distances[curNum] < distance) // 이미 확인했고, 더 짧다면 무시
			continue;
		treeNum++; // 무시되지 않는다면 fringe -> tree 노드가 됨
		if (curNum == destNum) // 도착 노드가 tree 됐다면 종료
			break;


		int next, nextDistance;
		adjacent* cur = roads[curNum];
		while (cur != NULL) { // 연결된 지역들 탐색
			next = cur->areaNum; // 연결된 지역 번호
			nextDistance = distance + cur->distance;
			if (nextDistance < distances[next]) { // 거리 갱신
				fringeQ.push({ next, nextDistance }); // fringe 큐에 넣기
				distances[next] = nextDistance;
				predecessor[next] = curNum; // 경로 추적을 위해 이전 노드 정보를 저장
			}
			cur = cur->next;
		}
	}

	if (distances[destNum] > 100000) cout << "None\n";
	else { // 역순으로 따라가며 경로 출력
		string str = "";
		int cur = destNum;
		while (cur != sourceNum) {
			str = to_string(cur) + " " + str;
			cur = predecessor[cur];
		}
		cout << treeNum << " " << sourceNum << " " << str << "\n";
	}
}

int main() {
	int nodeNum, edgeNum, questionNum, areaNum, flooded;
	string areaName;
	cin >> nodeNum >> edgeNum >> questionNum;

	for (int i = 0; i < nodeNum; i++) {
		cin >> areaNum >> areaName >> flooded;
		if (flooded == 0) {
			areas[areaNum] = areaName; // 침수되지 않은 지역만 넣음(어차피 계산에 안쓰이니까)
		}
	}

	int areaNum1, areaNum2, distance;
	for (int i = 0; i < edgeNum; i++) {
		cin >> areaNum1 >> areaNum2 >> distance;
		if (areas[areaNum1] != "" && areas[areaNum2] != "") { //침수되지 않은 지역만 넣음
			//방향이 없으니까 양쪽에 다 넣어야 한다. (연결 리스트 끝에 붙인다)
			adjacent* cur = roads[areaNum1];
			if (cur == NULL) {
				roads[areaNum1] = new adjacent(areaNum2, distance);
			}
			else {
				while (cur->next != NULL) {
					cur = cur->next;
				}
				cur->next = new adjacent(areaNum2, distance);
			}
			cur = roads[areaNum2];
			if (cur == NULL) {
				roads[areaNum2] = new adjacent(areaNum1, distance);
			}
			else {
				while (cur->next != NULL) {
					cur = cur->next;
				}
				cur->next = new adjacent(areaNum1, distance);
			}
		}
	}

	char mode; int sourceNum, destNum;
	for (int i = 0; i < questionNum; i++) {
		cin >> mode >> sourceNum >> destNum;
		if (mode == 'A') minDist(sourceNum, destNum);
		else minRoute(sourceNum, destNum);
	}
}
