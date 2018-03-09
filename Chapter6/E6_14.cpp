/*
例题6-14 补全了整个代码
测试数据如下：
3 3
3 1 N
3 3
6
1 1 NR WL *
1 2 WLF NR ER *
1 3 ER NL *
2 1 NF WR SL *
2 2 WF SL EFL *
2 3 EL SFR *
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
using namespace std;

struct Node{ int r; int c; int dir; 
Node() :r(0), c(0), dir(-1){}
Node(int r, int c, int dir) :r(r), c(c), dir(dir){}};

const char* dirs = "NESW";	// 顺时针
const char* turns = "FLR";
const int dr[] = { -1, 0, 1, 0 };
const int dc[] = { 0, 1, 0, -1 };
const int maxn = 9 + 2;
int d[maxn][maxn][4];	// 到起始点的最短距离
Node p[maxn][maxn][4];	// 父节点
short has_edge[maxn][maxn][4][3];	// 在(r,c)朝向某个方向是否可以沿三个方向走
int r0, c0, dir, r1, c1;		// 起始点
int r2, c2;				// 终点
int M, N;

int dir_id(char c){ return strchr(dirs, c) - dirs; }
int turn_id(char c){ return strchr(turns, c) - turns; }
bool inside(int r, int c){ return r >= 1 && r <= M && c >= 1 && c <= N; }	// 坐标从(1,1)开始

Node walk(const Node& u, int turn){
	int dir = u.dir;
	if (turn == 1) dir = (dir + 3) % 4;		// 左转
	if (turn == 2) dir = (dir + 1) % 4;		// 右转
	return Node(u.r + dr[dir], u.c + dc[dir], dir);		// 下一个结点，十分简洁
}

void print_ans(Node u){
	vector<Node> nodes;
	while (1){
		nodes.push_back(u);
		if (d[u.r][u.c][u.dir] == 0) break;
		u = p[u.r][u.c][u.dir];
	}
	nodes.push_back(Node(r0, c0, dir));
	int cnt = 0;
	for (int i = nodes.size() - 1; i >= 0; i--){
		if (cnt % 10 == 0) printf(" ");
		printf(" (%d,%d)", nodes[i].r, nodes[i].c);
		if (++cnt % 10 == 0) printf("\n");
	}
	if (nodes.size() % 10 != 0) printf("\n");
}

void solve(){			// bfs
	queue<Node> q;
	memset(d, -1, sizeof(d));
	Node u(r1, c1, dir);
	d[u.r][u.c][u.dir] = 0;
	q.push(u);
	while (!q.empty()){
		Node u = q.front(); q.pop();
		if (u.r == r2 && u.c == c2){ print_ans(u); return; }	// 到达终点
		for (int i = 0; i < 3; i++){
			Node v = walk(u, i);
			if (has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) && d[v.r][v.c][v.dir] < 0){
				d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
				p[v.r][v.c][v.dir] = u;
				q.push(v);
			}
		}
	}
	printf("No Solution Possible.\n");	// 无解
}

void read_node(){
	cin >> M >> N;	// 迷宫 M*N
	char ch;
	cin >> r0 >> c0 >> ch;	// 起点及方向
	cin >> r2 >> c2;		// 终点
	dir = dir_id(ch);
	r1 = r0 + dr[dir];		// 计算r1,c1
	c1 = c0 + dc[dir];
	memset(has_edge, 0, sizeof(has_edge));	// 初始化has_edge:没有方向
	int T; cin >> T;
	while (T--){
		string s; cin.sync();	// 清空缓存区	
		getline(cin, s);		// 每个结点读一行
		int r = s[0] - '0';
		int c = s[2] - '0';
		for (size_t i = 4; i < s.size() && s[i] != '*'; i++){
			if (strchr(dirs, s[i])){
				int d = dir_id(s[i]);
				while (s[++i] != ' '){
					int t = turn_id(s[i]);
					has_edge[r][c][d][t] = 1;
				}
			}
		}
	}
}

int main()
{
	read_node();
	solve();
	return 0;
}

