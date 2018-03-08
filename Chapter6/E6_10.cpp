// 例题6-10 by:LiuRujia

#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 10000;
int sum[maxn];

void build(int p){
	int v; cin >> v;
	if (v == -1) return;
	sum[p] += v;
	build(p - 1);
	build(p + 1);
}

bool init(){
	int v; cin >> v;
	if (v == -1) return false;
	memset(sum, 0, sizeof(sum));
	int pos = maxn / 2;
	sum[pos] = v;		// 从数组中间保存根结点
	build(pos - 1);		// 先序 - 向左 - 向右
	build(pos + 1);
	return true;
}

int main()
{
	int kase = 0;
	while (init()){
		int p = 0;
		while (sum[p] == 0) p++;	// 找到最左端的点
		cout << "Case " << ++kase << ":\n" << sum[p++];
		while (sum[p] != 0) cout << " " << sum[p++];
		cout << "\n\n";
	}
	return 0;
}
