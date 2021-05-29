#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct comp {
	bool operator()(pair<int, int> a, pair<int, int> b) {
		if (a.second == b.second) return a.first > b.first;
		else return a.second > b.second;
	}
};

string areas[1000000]; // 지역 이름을 저장하기 위한 배열
int distances[1000000]; // 최단거리를 저장하기 위한 배열
int predecessor[1000000]; // 경로를 추적하기 위한 배열
vector<vector<pair<int, int>>> roads(1000000); // 도로를 저장하기 위한 adjacency list


void minDist(int sourceNum, int destNum) {
	if (areas[sourceNum] == "" || areas[destNum] == "") { // 침수된 지역이 포함되었으면
		cout << "None\n";
		return;
	}
		
	int treeNum = 0;
	for (int i = 100000; i < 1000000; i++) distances[i] = 1000000; // 최대 거리로 배열 초기화
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> fringeQ; // fringe node를 저장하기 위한 우선순위 큐

	fringeQ.push({ sourceNum,0 });
	distances[sourceNum] = 0;

	int curNum, distance;
	while (!fringeQ.empty()) {
		curNum = fringeQ.top().first; // 현재 지역 번호
		distance = fringeQ.top().second; // 거리
		fringeQ.pop();

		if (distance > distances[curNum]) // 이미 확인했고, 더 짧다면 무시
			continue; 
		treeNum++; // 무시되지 않는다면 fringe -> tree 노드가 됨

		if (curNum == destNum) // 도착 노드가 tree 됐다면 종료
			break;

		int next, nextDistance;
		for (int i = 0; i < roads[curNum].size(); i++) { // 연결된 지역들 탐색
			next = roads[curNum][i].first; // 연결된 지역 번호
			nextDistance = roads[curNum][i].second + distance;
			if (distances[next] > nextDistance) { // 거리 갱신
				distances[next] = nextDistance;
				fringeQ.push({ next, nextDistance });
			}
		}
	}

	if (distances[destNum] > 100000) cout << "None\n";
	else
		cout << treeNum << " " << distances[destNum] << " " << areas[sourceNum] << " " << areas[destNum] << "\n";
}

void minRoute(int sourceNum, int destNum) {
	if (areas[sourceNum] == "" || areas[destNum] == "") { // 침수된 지역이 포함되었으면
		cout << "None\n";
		return;
	}

	int treeNum = 0;
	for (int i = 0; i < 1000000; i++) distances[i] = 1000000; // 최대 거리로 배열 초기화
	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> fringeQ; // fringe node를 저장하기 위한 우선순위 큐

	fringeQ.push({ sourceNum,0 });
	distances[sourceNum] = 0;

	int curNum, distance;
	while (!fringeQ.empty()) {
		curNum = fringeQ.top().first; // 현재 지역 번호
		distance = fringeQ.top().second; // 거리
		fringeQ.pop();

		if (distance > distances[curNum]) // 이미 확인했고, 더 짧다면 무시
			continue;
		treeNum++; // 무시되지 않는다면 fringe -> tree 노드가 됨

		if (curNum == destNum) // 도착 노드가 tree 됐다면 종료
			break;

		int next, nextDistance;
		for (int i = 0; i < roads[curNum].size(); i++) { // 연결된 지역들 탐색
			next = roads[curNum][i].first; // 연결된 지역 번호
			nextDistance = roads[curNum][i].second + distance;
			if (distances[next] > nextDistance) { // 거리 갱신
				distances[next] = nextDistance;
				fringeQ.push({ next, nextDistance });
				predecessor[next] = curNum;
			}
		}
	}

	if (distances[destNum] > 100000) cout << "None\n";
	else {
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
			roads[areaNum1].push_back({ areaNum2,distance });
			//방향이 없으니까 양쪽에 다 넣어야 한다.
			roads[areaNum2].push_back({ areaNum1,distance });
		}
	}

	char mode; int sourceNum, destNum;
	for (int i = 0; i < questionNum; i++) {
		cin >> mode >> sourceNum >> destNum;
		if (mode == 'A') minDist(sourceNum, destNum);
		else minRoute(sourceNum, destNum);
	}
}
