// 例题6-7 by:LiuRujia

#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 300;
bool failed;
struct Node{
	bool hava_value;
	int v;
	Node *left, *right;
	Node() :hava_value(false), left(NULL), right(NULL){}
}*root;
Node* newnode(){ return new Node(); }
void remove_tree(Node* u){
	if (u == NULL) return;
	remove_tree(u->left);
	remove_tree(u->right);
	delete u;
}
void addnode(int v, char *s){		// 建立树
	int n = strlen(s);
	Node* u = root;
	for (int i = 0; i < n - 1; i++){
		if (s[i] == 'L'){
			if (u->left == NULL) u->left = newnode();
			u = u->left;
		}
		else if (s[i] == 'R'){
			if (u->right == NULL) u->right = newnode();
			u = u->right;
		}
	}
	if (u->hava_value) failed = true;
	u->v = v;
	u->hava_value = true;
}

bool read_input(){
	failed = false;
	remove_tree(root);		// 先回收内存
	root = newnode();
	char s[maxn];
	while (1){
		if (scanf("%s", s) != 1) return false;
		if (!strcmp(s, "()")) break;
		int v;
		sscanf(&s[1], "%d", &v);
		addnode(v, strchr(s, ',') + 1);
	}
	return true;
}

bool bfs(vector<int> &ans){
	queue<Node*> q;
	ans.clear();
	q.push(root);
	while (!q.empty()){
		Node* u = q.front(); q.pop();
		if (!u->hava_value) return false;
		ans.push_back(u->v);
		if (u->left != NULL) q.push(u->left);
		if (u->right != NULL) q.push(u->right);
	}
	return true;
}

int main()
{
	read_input();
	vector<int> ans;
	if (!bfs(ans)) { ans.clear(); ans.push_back(-1); }	// 错误输出-1
	for (vector<int>::iterator i = ans.begin(); i != ans.end(); i++)
		printf("%d ", *i);
	printf("\n");
	return 0;
}
