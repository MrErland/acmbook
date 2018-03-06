
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
#define NOEXIT -1

struct Book{ 
	string author; string title; 
	bool operator < (const Book& b) const{
		return author == b.author ? title < b.title : author < b.author;
	}
};
vector<Book> lib;		// 图书馆内
vector<Book> box;		// 还书暂存

int findIndex(const string& title){
	for (unsigned int i = 0; i < lib.size(); i++){
		if (title == lib[i].title) return i;
	}
	return NOEXIT;		// no exit
}

void printLib(vector<Book>& lib){
	cout << "--Books--" << endl;
	for (unsigned int i = 0; i < lib.size(); i++){
		cout << "Title: " << lib[i].title << "\t" << "Author: " << lib[i].author << endl;
	}
	cout << "--end--" << endl;
}

void bow(){
	string tle;
	if (lib.empty()){ cout << "There is no book left." << endl; return; }
	printLib(lib);
	cout << "Title of the book would you like to borrow (q to quit): " << endl;
	while (cin >> tle){
		if (tle == "q") break;
		int index = findIndex(tle);
		if (index == NOEXIT) cout << "No exit this book: " << tle << endl;
		else lib.erase(lib.begin() + index, lib.begin() + index + 1);
	}
	printLib(lib);		// 打印内部书
}

void rtn(){
	string s, t;
	Book b;
	cout << "Input books you would return (q to quit): " << endl;
	while (cin >> s){
		if (s == "q") break;
		else {
			cin >> t;
			b.title = s; b.author = t;
			cout << "Title: " << b.title << "\t" << "Author: " << b.author << endl;
			box.push_back(b);
		}
	}
	if (!box.empty()){
		cout << "Ready for shelve: " << endl;
		sort(box.begin(), box.end());
		printLib(box);			// 打印暂存区
	}
}

void sle(){
	if (box.empty()) { cout << "No books to shelve." << endl; return; }
	unsigned int i, j = 0;
	for (i = 0; i < box.size(); i++){		// box排序后可以将其优化: 第二个元素插入的位置必定在第一个之后
		Book tmp = box[i];
		int pre = 0;
		for (; j < lib.size(); j++){
			if (lib[j].author > tmp.author || (lib[j].author == tmp.author && lib[j].title > tmp.title)){
				pre = j - 1;
				lib.insert(lib.begin() + j, tmp);
				cout << "New book in Library: " << tmp.title << "\t" << pre + 1 << endl;	// 从1开始计数
				j--; break;
			}
			else if (j == lib.size() - 1){
				lib.push_back(tmp);
				pre = j;
				cout << "New book in Library: " << tmp.title << "\t" << pre + 1 << endl;	// 从1开始计数
				j--; break;
			}
		}
	}
	box.clear();
	printLib(lib);
}

int main()
{
	int n;
	Book tmp;
	cout << "How many books?" << endl;
	cin >> n;
	cout << "Please input these books (title author): " << endl;
	for (int i = 0; i < n; i++){
		string s, t;
		cin >> s; tmp.title = s;
		cin >> t; tmp.author = t;
		lib.push_back(tmp);
	}
	sort(lib.begin(), lib.end());		// 按照作者、标题排序
	printLib(lib);
	cout << "Please input command (q to quit): ";
	string cmd;
	while (cin >> cmd)
	{
		if (cmd == "q") break;
		else if(cmd == "BORROW" || cmd == "borrow")
			bow();
		else if (cmd == "RETURN" || cmd == "return")
			rtn();
		else if (cmd == "SHELVE" || cmd == "shelve")
			sle();
		cout << "Please input command (q to quit): ";
	}
	return 0;
}
