// 例题6-8 by:LiuRujia 根据中序和后序遍历建树 + dfs

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
const int maxv = 10000 + 10;
int in_order[maxv], post_order[maxv];
int lch[maxv], rch[maxv];	// 左结点 右结点
int n;

bool read_list(int *a){			// 读取一行数字
	string line;
	if (!getline(cin, line)) return false;
	stringstream ss(line);
	n = 0;
	int x;
	while (ss >> x) a[n++] = x;
	return n > 0;
}

int build(int L1, int R1, int L2, int R2){		// L1...R1 中序		L2...R2 后序
	if (L1 > R1) return 0;
	int root = post_order[R2];
	int p = L1;
	while (in_order[p] != root) p++;
	int cnt = p - L1;		// 左子树结点个数
	lch[root] = build(L1, p - 1, L2, L2 + cnt - 1);
	rch[root] = build(p + 1, R1, L2 + cnt, R2 - 1);
	return root;
}

int best, best_sum;
void dfs(int u, int sum){
	sum += u;
	if (!lch[u] && !rch[u]){		// 是一个叶结点
		if (sum < best_sum || (sum == best_sum && u < best)){
			best = u; best_sum = sum;
		}
	}
	if (lch[u])dfs(lch[u], sum);
	if (rch[u])dfs(rch[u], sum);
}

int main()
{
	while (read_list(in_order)){
		read_list(post_order);
		build(0, n - 1, 0, n - 1);
		best_sum = 1 << 20;
		dfs(post_order[n - 1], 0);
		cout << best << "\n";
	}
	return 0;
}
