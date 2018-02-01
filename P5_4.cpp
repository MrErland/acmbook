
#include<list>
#include<cstdio>

using namespace std;
struct Student{ int id; int from; int to; };

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n){
		list<Student> a;			// 需要频繁的删除操作，使用list而不是vector
		Student t;
		for (int i = 0; i < n; i++){	// 初始化
			scanf("%d%d", &t.from, &t.to);  // A -> B
			t.id = i;			// id: 0 -- n-1 
			a.push_back(t);
		}
		if (a.size() % 2 == 1) { printf("No\n"); continue; }	// 奇数时不用判断
		while (!a.empty())
		{
			bool b = false;
			list<Student>::iterator head = a.begin();
			list<Student>::iterator i = head;
			for (i++; i != a.end(); i++){
				if (head->from == i->to && head->to == i->from){	// 存在匹配, 删除当前位置和首位置
					b = true;
					a.erase(i);	
					a.erase(head);
					break;
				}
			}
			if (b) continue;
			else { printf("No\n"); break; }		// 存在不匹配的学生
		}
		if (a.empty())  printf("Yes\n"); 
	}
	return 0;
}
