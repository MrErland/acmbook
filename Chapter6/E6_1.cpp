#include <deque>
#include <queue>
#include <string>
#include <iostream>
using namespace std;
int t1, t2, t3, t4, t5, Q;
struct prog{
	int n;					// 序号
	int size;				// 语句数目
	string line[30];		// 语句
	int now = 0;			// 执行位置
};
deque<prog> wt;		// 等待队列
queue<prog> bk;		// 阻塞队列
string vars[30] = {"0"};		// 变量集: var 为小写字母 var[var - 'a'] 

int main()
{
	int n, m, i = 1;
	cin >> n;	
	while (n--){
		cin >> m;
		getchar();
		int j = 0;
		prog p;
		p.n = i++;
		p.size = m;
		while (m--){ getline(cin, p.line[j++]); }
		wt.push_back(p);
	}
	cin >> t1 >> t2 >> t3 >> t4 >> t5 >> Q;

	bool islock = false;	// 锁标记
	while (!wt.empty()){
		prog p = wt.front(); wt.pop_front();
		if (p.now < p.size){		// 这个程序还没执行完
			int t = 0;				// 已执行时间
			while (t < Q && p.now < p.size){
				string s = p.line[p.now]; p.now++;	// 取出第一个语句
				if (s.find("=") != string::npos){	// 赋值语句
					char var = s[0]; 
					vars[var - 'a'] = s.substr(2);
					t += t1;
				}
				else if (s.find("print ") != string::npos){		// 打印语句
					char var = s[s.length() - 1];
					cout << p.n << " " << var << "=" << vars[var - 'a'] << endl;
					t += t2;
				}
				else if (s == "end"){		
					t += t5;
				}
				else if (s == "lock" && islock){	// 已经有锁
					bk.push(p);
					break;
				}
				else if (s == "lock" && !islock){	// 还没有锁
					islock = true;
					t += t3;
				}
				else if (s == "unlock"){		// 解锁
					islock = false;
					if (!wt.empty()) { wt.push_front(bk.front()); bk.pop(); }
					t += t4;
				}
			}
			if (p.now < p.size) wt.push_back(p);	// 没有执行完，进入等待队列
		}
	}
	return 0;
}
