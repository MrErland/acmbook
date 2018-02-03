
#include <cstdio>
#include <deque>
using namespace std;
deque<int> printer;
int n;

int getLevel(){
	int lev = -1;
	for (deque<int>::iterator i = printer.begin(); i != printer.end(); i++){
		if (*i > lev) lev = *i;
	}
	return lev;
}

int main()
{
	while (scanf("%d", &n) == 1 && n)	// 任务数目
	{
		int time = 0, t;
		for (int i = 0; i < n; i++){		// 初始状态 
			scanf("%d", &t);
			printer.push_back(t);
		}
		int index, lev;
		while (scanf("%d", &index) == 1) if (index >= 0 && index < n) break;	// 目标索引
		lev = printer[index];		 // 目标索引的等级
		int now = 0;
		while (index >= 0)
		{
			t = printer.front();			// 拿出队首
			now = getLevel();
			printer.pop_front();
			if (index > 0){
				if (now == t) time++; 		// 具有最高优先级, 进入打印
				else printer.push_back(t); 		// 推入队尾
				index--;			// 目标索引前移
			}
			else{
				if (now == lev) { printf("%d\n", ++time); break; }		// 成功打印
				else { printer.push_back(lev); index = printer.size() - 1; }	// 回到队尾
			}
		}
	}
	return 0;
}
