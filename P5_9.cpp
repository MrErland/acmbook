// From: http://blog.csdn.net/majing19921103/article/details/44409711

#include <iostream>  
#include <string>  
#include <map>   
#include <stack>  
using namespace std;
map<string, int> array_table;			// 数组-大小
map<string, map<int, int>> array_value_table;

void partition(string origin, string &left, string &right){		// 根据是否赋值，拆分字符串
	int index = origin.find_first_of('=', 0);
	if (index != -1){
		left = origin.substr(0, index);
		right = origin.substr(index + 1);
	}
	else{
		left = origin;
		right = "";
	}
}

void getArray(string str, string &name, string &value){		// 对数组结构分析
	int begin = str.find_first_of('[', 0);
	int end = str.find_last_of(']');
	if (begin != -1){
		name = str.substr(0, begin);
		value = str.substr(begin + 1, end - begin - 1);
	}
	else{
		name = "";
		value = str;
	}
}

int calculateArray(string str){
	string name, value;
	getArray(str, name, value);
	stack<string> s;
	int ans;
	while (name != ""){
		string left, right;
		getArray(value, left, right);
		if (array_table.count(name) == 0)	return -1;
		value = right;
		s.push(name);
		name = left;
	}
	ans = atoi(value.c_str());
	if (ans < 0) return -1;
	while (!s.empty()){
		string left = s.top();
		int num = array_table[left];
		if (ans >= num)	return -1;
		if (array_value_table[left].count(ans) == 0) return -1;
		ans = array_value_table[left][ans];
		s.pop();
	}
	return ans;
}

int main()
{
	string str;
	bool mark = false, isfirst = true;
	int num = 0;
	while (cin >> str)
	{
		if (str != "."){
			mark = false;
			num++;
			string left, right;
			partition(str, left, right);
			if (right == ""){				// 声明语句
				string name, value;
				getArray(left, name, value);
				array_table[name] = atoi(value.c_str());	// 在map中插入数组-大小的键值对
			}
			else{							// 赋值语句
				string name, value;
				int ans, temp;
				getArray(left, name, value);
				temp = calculateArray(value);
				ans = calculateArray(right);
				if (temp >= 0 && temp < array_table[name] && ans != -1)
					array_value_table[name][temp] = ans;
				else if (isfirst){
					cout << num << endl;
					isfirst = false;
				}
			}
		}
		else{
			array_table.clear();
			array_value_table.clear();
			if (mark) break;
			else{
				if (isfirst) cout << 0 << endl;
				mark = true;
				isfirst = true;
				num = 0;
			}
		}
	}
	return 0;
}
