// 例题 6-2 铁轨  from: LiuRujia

#include <cstdio>
#include <stack>
using namespace std;
const int MAXN = 1000 + 10;
int n, target[MAXN];

int main()
{
	while (scanf("%d", &n) == 1){
		stack<int> s;
		int A = 1, B = 1;
		for (int i = 1; i <= n; i++)
			scanf("%d", &target[i]);
		int ok = 1;			// 标记结果
		while (B <= n){		// 依次判断B的每一位是否可以输出
			if (A == target[B]){ A++; B++; }	// A输入刚好等于B的首位
			else if (!s.empty() && s.top() == target[B]) { s.pop(); B++; }	// B的首位恰好是栈顶
			else if (A <= n) s.push(A++);	// 只能下一节车厢入栈
			else { ok = 0; break; }		// 无法输出
		}
		printf("%s\n", ok ? "Yes" : "No");
	}
	return 0;
}
