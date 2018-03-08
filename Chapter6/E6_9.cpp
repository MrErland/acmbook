// 例题6-9 by:LiuRujia
// 递归代码非常简洁和巧妙

#include <iostream>
using namespace std;

bool solve(int& W){				// 注意此处是传地址，每计算一个子天平的状态，保存两侧总重量！
	int W1, D1, W2, D2;			// 即上一层天平两侧的重量为其下所有层重量之和
	bool b1 = true, b2 = true;
	cin >> W1 >> D1 >> W2 >> D2;
	if (!W1) b1 = solve(W1);
	if (!W2) b2 = solve(W2);
	W = W1 + W2;
	return b1 && b2 && (W1*D1 == W2*D2);
}

int main()
{
	int T, W;
	cin >> T;
	while (T--){
		if (solve(W)) cout << "Yes";
		else cout << "No"; 
		cout << " " << W << "\n";		// 砝码总重量
	}
	return 0;
}
