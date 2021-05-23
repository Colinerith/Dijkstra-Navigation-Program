# Dijkstra-Navigation-Program
Algorithm) Dijkstra

[내비게이션 프로그램 설계]
1. 과제 개요  
인하내비에서는 도로교통상황을 파악하여, 출발지부터 목적지까지의 최적경로를 안내하는 내비게이션 애플리케이션을 서비스하고 있다.  
한편, 태풍으로 인해 우리나라의 많은 지역이 침수되었다.  
출발지에서 목적지로 가는 경로 중 침수된 지역을 피하여 안전하고 가장 빠른 경로를 안내하려 한다.  
이를 위해 출발지와 목적지 간의 안전한 최단경로를 Dijkstra 알고리즘을 이용하여 계산하자.  
먼저 도로공사에서 각 지역들과 지역 간의 도로 정보들을 입력받은 뒤, 아래에 제시된 기능들을 수행하는 프로그램을 구현하시오.  
단, 모든 도로는 양방향 도로라 가정하고, Dijkstra 알고리즘에서 decreaseKey() 함수는 정점의 최단거리가 더 작아지는 경우에만 수행된다.  

2. 정보 형식  
  (1) 지역 정보  
    ① 지역번호 (기준키, 유일함): 100,000 ~ 999,999 사이의 정수.  
    ② 지역이름: 공백 없는 20Byte 이내의 문자열. 예) “Juan-dong”  
    ③ 침수여부: 1 또는 0. 예) “1” (침수된 경우), “0” (침수되지 않은 경우)  
  (2) 두 지역 간 도로 정보  
    ① 지역번호1: 하나의 지역번호  
    ② 지역번호2: 지역번호1과 다른 지역번호  
    ③ 도로의 거리: 1 ~ 5,000 사이의 정수  
  
3. 수행할 기능  
  (1) 데이터 입력받기  
    프로그램을 실행하면 무향그래프(undirected graph) 정보를 표준입력(standard input)으로 입력받아, 인접리스트 기반(adjacency list representation) 그래프자료구조를 생성하여 관리한다.  
    첫 번째 줄에는 지역정보의 수 n(2 ≤ n ≤ 100000)과 지역 간의 도로 정보의 수 m(1 ≤ m ≤ 200000), 질의의 수 q(1 ≤ q ≤ 50)가 공백으로 구분되어 주어진다.  
    이후 m개의 줄을 통해, 지역정보가 한 줄로 주어지고, 각 필드는 공백으로 구분된다. [지역번호/지역이름/침수여부]   
    이후 n개의 줄을 통해, 지역 간 도로 정보가 한 줄로 주어지며, 각 필드는 공백으로 구분된다. [지역번호1/지역번호2/도로의 거리]  
    단, 최대거리는 1000000이며, 출발지에서 목적지까지의 거리가 1000000을 초과하면 출발지에서 목적지까지 갈 수 없다고 가정한다.
  (2) 두 지역 간의 최단거리 찾기  
    - 질의형식: “A S D”
    A: 최단거리 찾기에 대한 질의
    S: 출발 지역번호
    D: 목적 지역번호
    - 출력형식: “N W SN DN” or “None”
    N: 출발지부터 목적지까지 Tree vertex들의 set에 추가된 지역들의 수
    W: 출발지부터 목적지까지의 최단거리
    SN: 출발 지역이름
    DN: 목적 지역이름
    - 설명: 출발지와 목적지가 주어지면, 두 지역 간의 최단거리를 계산한다. 만약 계산 중 최단거리가 동일한 후보정점이 2개 이상 존재한다면, 지역번호가 더 작은 정점(높은 우선순위)을 우선적으로 계산한다. 출발지부터 목적지까지의 최단경로를 계산했을 때, Tree vertex가 된 지역들의 수(N), 최단거리, 출발 지역이름, 목적 지역이름을 표준출력(standard output)으로 공백으로 구분하여 출력한다. 만약 출발지 또는 목적지가 침수되어 있거나 두 지역의 최단거리가 1000000을 초과하는 경우, “None”을 출력한다.  
  (3) 두 지역 간의 최단경로 찾기
- 질의형식: “B S D”
B: 최단경로 찾기에 대한 질의
S: 출발 지역번호
D: 목적 지역번호
- 출력형식: “N V0, ... Vk ” or “None”
N: 출발지부터 목적지까지 Tree vertex들의 set에 추가된 지역들의 수
V0, ... Vk: 출발지부터 목적지까지의 최단경로 (Vi: 지역번호, V0: 출발지, Vk: 목적지)
- 설명: 출발지와 목적지가 주어지면, 두 지역 간의 최단경로를 계산한다. 만약 계산 중 최단거리가 동일한 후보정점이 2개 이상 존재한다면, 지역번호가 더 작은 정점(높은 우선순위)을 우선적으로 계산한다. 출발지부터 목적지까지의 최단경로를 계산했을 때, Tree vertex가 된 지역들의 수(N)와 최단경로를 표준출력으로 공백으로 구분하여 출력한다. 만약 출발지 또는 목적지가 침수되어 있거나 두 지역의 최단거리가 1000000을 초과하는 경우, “None”을 출력한다.

4. 입출력 제한사항
  (1) 프로그램의 한 입력에 대해 정점 정보는 최대 100000개, 간선 정보는 최대 200000개, 질의는 최대 50개가 입력된다.
  (2) 채점서버의 입력들에 대해 총 2초의 제한시간 이내에 수행되어야 한다.
  (3) 제시한 입출력 형식대로 표준입출력을 사용하여 처리한다.
  (4) 문제에서 설명되지 않은 예외처리를 해야 할 질의는 입력되지 않는다.
