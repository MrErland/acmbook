// 例题6-4  在已给代码上根据我自己的理解，做了修改，效率稍微有些降低。

#include <cstdio>
using namespace std;
const int maxn = 100000 + 5;
int n, right[maxn], left[maxn];
void link(int L, int R){ right[L] = R; left[R] = L; }
void rev(){
	int b = 0;
	for (int i = 0; i <= n; i++){
		b = right[b];
		right[b] = left[b];
	}
}
//void swap(int L, int R){ 
//	int r = right[L]; int l = left[L];
//	right[L] = right[R]; left[L] = left[R];
//	right[R] = r; left[R] = l;
//}

int main()
{
	int m, kase = 0;
	while (scanf("%d%d", &n, &m) == 2){
		for (int i = 1; i <= n; i++){
			left[i] = i - 1;                // 初始化每个点的左侧点 0,1,2...
			right[i] = (i + 1) % (n + 1);	// 初始化每个点的右侧点 2,3,4... 0
		}
		right[0] = 1; left[0] = n;		// 0 
		int op, X, Y;
		while (m--){
			scanf("%d", &op);
			if (op == 4) rev(); 		// 翻转整个链表，时间复杂度：N
			else {
				scanf("%d%d", &X, &Y);
				if (op == 1 && X == left[Y]) continue;
				else if (op == 2 && X == right[Y]) continue;
				else{
					int LX = left[X], RX = right[X], LY = left[Y], RY = right[Y];
					if (op == 1) { link(LX, RX); link(LY, X); link(X, Y); }
					else if (op == 2){ link(LX, RX); link(X, RY); link(Y, X); }
					else if (op == 3){ link(LX, Y); link(Y, RX); link(LY, X); link(X, RY); }
				}
			}
		}

		int b = 0;
		long long ans = 0;
		for (int i = 1; i <= n; i++){
			b = right[b];
			if (i % 2 == 1) ans += b;
		}
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}
