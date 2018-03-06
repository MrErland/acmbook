
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n){
		vector<int> a(n);
		for (int i = 0; i < n; i++)			// 初始化 用vector的底作为牌顶
			a[i] = n - i;
		while (a.size() >= 2){
			int f, s;
			f = a.back(); a.pop_back();
			s = a.back(); a.pop_back();
			a.insert(a.begin(), s);
			printf("%d ", f);
		}
		printf("%d\n", a[0]);
	}
	return 0;
}
