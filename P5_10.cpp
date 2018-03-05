
/*
 本解答将问题简化：每篇文章即为一行，简化输入。
 解决思路：先将请求分类，再从文章数组中查找符合要求的元素，打印即可。
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> art;

int findArt(string s, string t, string mod){		// 在art每个字符串中查找目标s
	if (mod == "NOT" || mod == ""){
		for (size_t i = 0; i < art.size(); i++){
			size_t f = art[i].find(s);
			if (mod == "NOT" && f == string::npos) return i;
			if (mod == "" && f != string::npos) return i;
		}
		return -1;
	}
	for (size_t i = 0; i < art.size(); i++){		
		size_t f1 = art[i].find(s);	
		size_t f2 = art[i].find(t);
		if (mod == "AND"){
			if (f1 != string::npos && f2 != string::npos)
				return i;
		}
		else if (mod == "OR"){
			if (f1 != string::npos || f2 != string::npos)
				return i;
		}
	}
	return -1;		
}

int findMod(string s, string t){
	size_t r = s.find(t);
	if (r != string::npos) return r;
	else return -1;
}

int main()
{
	int n, m;
	cin >> n;
	getchar();			// 读取缓冲区的换行符
	while (n--){
		string s;
		getline(cin, s);
		art.push_back(s);
	}
	cin >> m;
	getchar();
	while (m--){		// 先判断问题类型，再分解字符串
		string s;
		getline(cin, s);
		int m1, m2, m3;
		m1 = findMod(s, " AND ");
		m2 = findMod(s, " OR ");
		m3 = findMod(s, "NOT ");
		if (m1 != -1){
			string sub1, sub2;
			sub2 = s.substr(m1 + 5, s.length() - m1 - 5);
			sub1 = s.substr(0, s.length() - sub2.length() - 5);
			// cout << sub1 << ' ' << sub2 << endl;
			int f = findArt(sub1, sub2, "AND");
			if (f != -1) cout << art[f] << endl;
			else cout << "No Answer." << endl;
		}
		else if (m2 != -1){
			string sub1, sub2;
			sub2 = s.substr(m2 + 4, s.length() - m2 - 4);
			sub1 = s.substr(0, s.length() - sub2.length() - 4);
			// cout << sub1 << ' ' << sub2 << endl;
			int f = findArt(sub1, sub2, "OR");
			if (f != -1) cout << art[f] << endl;
			else cout << "No Answer." << endl;
		}
		else if (m3 != -1){
			string sub;
			sub = s.substr(4, s.length() - 4);
			int f = findArt(sub, "", "NOT");
			if (f != -1) cout << art[f] << endl;
			else cout << "No Answer." << endl;
		}
		else{
			int f = findArt(s, "", "");
			if (f != -1) cout << art[f] << endl;
			else cout << "No Answer." << endl;
		}
	}
	return 0;
}
