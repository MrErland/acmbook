
#include <vector>
#include <cstdio>
#include <map>
#include <string>
#include <iostream>
using namespace std;
map<string, long> old;
map<string, long> now;

void input(string s){
	while (getchar() != '{');
	string key;
	char c;
	while (c = getchar()) {
		if (c != ':') key += c;
		else {
			long tmp;
			scanf("%ld", &tmp);
			if (s == "old") old.insert(pair<string, long>(key, tmp));
			else now.insert(pair<string, long>(key, tmp));
			key = "";
			c = getchar();
			if (c == '}') break;
		}
	}
}

int main()
{
	// 读入两个字典的数据，保存到map中
	// 从旧字典开始扫描，查找与新字典的不同
	input("old");
	input("now");
	vector<string> add, del, mod;
	for (map<string, long>::iterator i = old.begin(); i != old.end(); i++){
		string s = i->first;
		long l = i->second;
		bool b = false;
		for (map<string, long>::iterator j = now.begin(); j != now.end(); j++){
			string t = j->first;
			long m = j->second;
			if (t == s){
				if (m != l) mod.push_back(s);	// 修改条目 注意：需要将之从now中删除，剩余则为新增的条目。
				now.erase(j);
				b = true;
				break;
			}
		}
		if (!b) del.push_back(s);		// 删除条目
	}
	for (map<string, long>::iterator j = now.begin(); j != now.end(); j++)
		add.push_back(j->first);  // 增加条目
	now.clear();
	cout << "+ ";
	for (size_t i = 0; i < add.size(); i++)
		cout << add[i] << " ";
	cout << '\n' << "- ";
	for (size_t i = 0; i < del.size(); i++)
		cout << del[i] << " ";
	cout << '\n' << "* ";
	for (size_t i = 0; i < mod.size(); i++)
		cout << mod[i] << " ";
	return 0;
}
