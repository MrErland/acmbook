
// 如果存在左右对称关系，最左侧的点一定对称于最右侧的点
// 因此从两个方向依次判断各点Y是否相同，再判断它们的中点是否重合即可

#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n;
struct Point{
	int x; int y; int id;
	bool operator < (const Point& b) const{		// 为了方便从两个方向进行搜索
		if (this->x == b.x) {
			if (b.id < n / 2)return  this->y > b.y;
			else return this->y < b.y;
		}
		else return this->x < b.x;
	}
};

int main()
{
	while (scanf("%d", &n) == 1 && n)		// input: n
	{
		vector<Point> a(n);
		for (int i = 0; i < n; i++){	// input: (x, y)
			scanf("%d%d", &a[i].x, &a[i].y);
			a[i].id = i; 
		}
		sort(a.begin(), a.end());

		int i = 0;		// 从首位
		int j = n - 1;		// 从尾部
		double mid = (a[i].x * 1.0 + a[j].x) / 2;	// 对称轴
		while (i < j)
		{
			if (a[i].y != a[j].y) break;
			if(mid != (a[i].x * 1.0 + a[j].x) / 2) break;
			i++; j--;
		}
		if (i - j == 2 && mid == a[i + 1].x * 1.0) { printf("Yes\n"); continue; }	// n % 2 == 1
		if (i >= j) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
