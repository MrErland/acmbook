// 例题6-6 by:LiuRujia

// 模拟法：模拟每个小球落下后开关的状态,效率不高
#include <cstdio>
#include <cstring>
using namespace std;
const int maxd = 20;
int s[1 << maxd];			// 开关状态

int main()
{
	int D, I;
	while (scanf("%d%d", &D, &I) == 2){
		memset(s, 0, sizeof(s));
		int k, n = (1 << D) - 1;
		for (int i = 0; i < I; i++){
			k = 1;			// 从顶点下落
			while (1){
				s[k] = !s[k];		// 反向变化
				k = s[k] ? k * 2 : 2 * k + 1;
				if (k > n) break;	// 越界
			}
		}

		printf("%d\n", k / 2);		// 最后一个球出界之前的叶子编号，非常巧妙...
	}
	return 0;
}

// 推导法：如果上一个小球经过父节点后向左，下一个经过此父节点的小球必然是向右，反之亦然；
//	则最后的第I个小球，当I是奇数时，它是往左的第(I+1)/2的小球；当I是偶数时，它是往右的第I/2个小球，往下类推。
#include <cstdio>
using namespace std;
int main()
{
	int D, I;
	while (scanf("%d%d", &D, &I) == 2){
		int k = 1;
		for (int i = 0; i < D - 1; i++){
			if (I % 2){ k = k * 2; I = (I + 1) / 2; }
			else { k = k * 2 + 1; I /= 2; }
		}
		printf("%d\n", k);
	}
	return 0;
}
