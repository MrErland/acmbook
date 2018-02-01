nclude<cstdio>
using namespace std;
const int maxn = 20;
const int times = 1000;
int n, a[maxn];

bool isNull(){
	for (int i = 0; i < n; i++){
		if (a[i] != 0)
			return false;
	}
	return true;
}

int getElement(int i){
	if (a[i] - a[i + 1] > 0) return a[i] - a[i + 1];
	else return a[i + 1] - a[i];
}

void print(){
	for (int i = 0; i < n; i++){
		printf("%d ", a[i]);
	}
	printf("-> ");
}

int main()
{
	while (scanf("%d", &n) == 1 && n){
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		bool zero = false;
		for (int i = 0; i < times; i++){
			if (isNull()) { zero = true; break; }
			int head = a[0], j;
			for (j = 0; j < n - 1; j++){
				a[j] = getElement(j);
			}
			if (a[j] - head > 0) a[j] = a[j] - head;
			else a[j] = head - a[j];
			print();
		}
		if (zero) printf("Yes\n");
		else printf("No\n");
	}

	return 0;
}
