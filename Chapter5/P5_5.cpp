
#include<iostream>
#include<string>
#include<set>

using namespace std;
set<string> a;

bool isCompound(string& s){
	if (s.find('-') != string::npos) return true;
	else return false;
}

int main()
{
	string s;
	while (cin >> s && s != "0"){
		if (isCompound(s)) a.insert(s);
	}
	for (set<string>::iterator i = a.begin(); i != a.end(); i++)
		cout << *i << endl;
	return 0;
}
